using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Data.SqlClient;
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
using System.Windows.Navigation;
using System.Windows.Shapes;
using DOVY.Models;

namespace DOVY
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }
        private void Button_Click(object sender, RoutedEventArgs e)
        {

                using (var context = new Entities())
                {
                    var userId = context.ValidateCredentials(UserName.Text, Password.Password);
                    switch (userId)
                    {
                        case -1:
                            FailureText.Content = "Username and/or password is incorrect.";
                            break;
                        default:
                            var system = new Jidelna(context.Users.First(u => u.Id == userId));
                            system.Show();
                            this.Close();
                            break;
                    }
                }
            

                FailureText.Content = "Error occured while logging.";
            
        }
    }
}
