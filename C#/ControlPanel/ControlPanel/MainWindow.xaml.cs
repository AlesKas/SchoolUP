using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Timers;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Diagnostics;
using System.Management;
using System.Dynamic;
using System.Windows.Threading;

namespace ControlPanel
{
    public partial class MainWindow : Window
    {
        private const float V = 16281.6F;     
        
        
        
        int s; //index of selected item

        Process[] processes = Process.GetProcesses();
        
        private Task listVievComp()
        {
            return Task.Run(() =>
            {
                foreach (Process process in processes)
                {
                    dynamic extraProcessInfo = GetProcessExtraInformation(process.Id);
                    proces item = new proces
                    {
                        ProcessName = process.ProcessName,
                        Id = process.Id,
                        Responding = status(process.Responding),
                        PrivateMemory = BytesToReadableValue(process.PrivateMemorySize64),
                        User = extraProcessInfo.Username,
                        Description = extraProcessInfo.Description

                    };
                    this.Dispatcher.Invoke(() => { ProcesLV.Items.Add(item); });
                }
            });
        }

        private string status(bool input)
        {
            return input ? "Responding" : "Not responding";
        }

        async void TabControl_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (Tasks != null && Tasks.IsSelected)
                await listVievComp();
            if (Performance != null && Performance.IsSelected)
            {
                while (true)
                {
                    await Perf();
                }
            }
        }
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            
        }


        private Task Perf()
        {
            return Task.Run(() =>
            {
                PerformanceCounter pCpu = new PerformanceCounter("Processor", "% Processor Time", "_Total");
                PerformanceCounter tempCount = new PerformanceCounter("Thermal Zone Information", "Temperature", @"\_TZ.THRM");
                PerformanceCounter RAM = new PerformanceCounter("Memory", "Available MBytes");
                PerformanceCounter pSys = new PerformanceCounter("System", "System Up Time");
                PerformanceCounter dataSentCounter = new PerformanceCounter("Network Interface", "Bytes Sent/sec", "Intel[R] Dual Band Wireless-AC 3168");
                PerformanceCounter dataReceivedCounter = new PerformanceCounter("Network Interface", "Bytes Received/sec", "Intel[R] Dual Band Wireless-AC 3168");

                float up = pSys.NextValue();
                float dataSent = dataSentCounter.NextValue();
                float fRam = RAM.NextValue();
                float fCpu = pCpu.NextValue();
                float dataRec = dataReceivedCounter.NextValue();
                Thread.Sleep(1000);
                fCpu = pCpu.NextValue();
                fRam = RAM.NextValue();
                up = pSys.NextValue();
                dataRec = dataSentCounter.NextValue();
                dataSent = dataReceivedCounter.NextValue();

                this.Dispatcher.Invoke(() =>
                {               
                    BS.Content = (dataSent / 1024) + "kB/s";
                    BR.Content = (dataRec / 1024) + "kB/s";
                    UPtime.Content = string.Format("{00:00:00:00}", up);
                    RAMuse.Content = string.Format("{0} MB used", (V - fRam));
                    CPUpb.Value = fCpu + 5;
                    RAMpb.Value = ((fRam / V) * 100);
                    CPUuse.Content = string.Format("{0:0.000} %", fCpu);
                    CPUtemp.Content = string.Format("{0} °C", (int)(tempCount.NextValue() - 273.15f));
                });
                
            });
        }

        private void Tick(object sender, EventArgs e)
        {
           /*         
            //RAM
            /*float fRam = V - pRam.NextValue();
            RAMuse.Content = string.Format("{0000} MB", fRam);
            RAMpb.Value = pRam.NextValue() / 140;
            
            //NETWORK
            

            listVievComp();
            //float fGpu = gpu.NextValue();
            //GPUusage.Content = string.Format("{0:0.000} %", fGpu);

            */
        }      

        private ExpandoObject GetProcessExtraInformation (int processId)
        {

            string query = "Select * From Win32_Process Where ProcessID = " + processId;
            ManagementObjectSearcher searcher = new ManagementObjectSearcher(query);
            ManagementObjectCollection processList = searcher.Get();
            //using MOS to get Description and User of process
            //OxpandoObject to add and delete members of it's instance

            dynamic response = new ExpandoObject();
            response.Description = "";
            response.Username = "Unknown";

            foreach (ManagementObject obj in processList)
            {
                string[] argList = new string[] { string.Empty, string.Empty };
                int returnVal = Convert.ToInt32(obj.InvokeMethod("GetOwner", argList));
                if (returnVal == 0)
                {
                    response.Username = argList[0];
                }

                if (obj["ExecutablePath"] != null)
                {
                    try
                    {
                        FileVersionInfo info = FileVersionInfo.GetVersionInfo(obj["ExecutablePath"].ToString());
                        response.Description = info.FileDescription;
                    }
                    catch { }
                }
            }

            return response;
        }

         public string BytesToReadableValue(long number)
         {
                List<string> suffixes = new List<string> { " B", " kB", " MB", " GB", " TB", " PB" };

                for (int i = 0; i < suffixes.Count; i++)
                {
                    long temp = number / (int)Math.Pow(1024, i + 1);

                    if (temp == 0)
                    {
                        return (number / (int)Math.Pow(1024, i)) + suffixes[i];
                    }
                }
                return number.ToString();
         }


        private void Button_Click(object sender, RoutedEventArgs e)
        {
            var proc = processes[s];
            try
            {
                proc.Kill();
                ProcesLV.Items.RemoveAt(ProcesLV.SelectedIndex);
            }
            catch (Exception ex)
            {
                System.Windows.MessageBox.Show(ex.Message, "Message", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
        private void ProcesLV_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            var item = sender as System.Windows.Controls.ListView;
            s = item.SelectedIndex;          
        }


        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            RunTask task = new RunTask();
            task.Show();
        }

        private void GetInfo(object sender, RoutedEventArgs e)
        {
            Info info = new Info(processes[s]);
            info.Show();
        }

        private void KillMenuS(object sender, RoutedEventArgs e)
        {
            var proc = processes[s];
            try
            {
                proc.Kill();
                ProcesLV.Items.RemoveAt(ProcesLV.SelectedIndex);
            }
            catch (Exception ex)
            {
                System.Windows.MessageBox.Show(ex.Message, "Message", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        private void ProcesLV_MouseDown(object sender, MouseButtonEventArgs e)
        {
            System.Windows.MessageBox.Show("Yes", "Mess", MessageBoxButton.OK, MessageBoxImage.None);
        }
    }
    internal class proces
    {
        public string ProcessName { get; set; }
        public int Id { get; set; }
        public string Responding { get; internal set; }
        public string PrivateMemory { get; internal set; }
        public string CPUuse { get; internal set; }
        public string CPUusage { get; internal set; }
        public object Description { get; internal set; }
        public object User { get; internal set; }
    }
 }