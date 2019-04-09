using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Diagnostics;

namespace ControlPanel
{
    /// <summary>
    /// Interakční logika pro RunTask.xaml
    /// </summary>
    public partial class RunTask : Window
    {
        public RunTask()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            if(!string.IsNullOrEmpty(OpenTask.Text))
            {
                try
                {
                    Process procs = new Process();
                    procs.StartInfo.FileName = OpenTask.Text;
                    procs.Start();
                    
                }
                catch(Exception ex)
                {
                    MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                }
                this.Close();
            }
            else
            {
                var s = MessageBox.Show("Do you want to exit?", "Alert", MessageBoxButton.YesNo, MessageBoxImage.Warning);
                if (s == MessageBoxResult.Yes)
                    this.Close();
            }
        }
    }
}
