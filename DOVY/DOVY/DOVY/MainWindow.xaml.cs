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
        public int Validate_User(string userName, string password)
        {
            var id = -1;
            using (SqlConnection conn = new SqlConnection(@"Data Source=(LocalDB)\MSSQLLocalDB;AttachDbFilename=C:\Users\alesk\OneDrive\Dokumenty\GitHub\SchoolUP\DOVY\DOVY\DOVY\DOVY.mdf;Integrated Security=True;Connect Timeout=30"))
            {
                SqlCommand sql = new SqlCommand("SELECT * FROM [dbo].[Users] WHERE UserName=@username AND Password=@password;", conn);
                sql.Parameters.AddWithValue("@username", userName);
                sql.Parameters.AddWithValue("@password", password);

                conn.Open();
                using(var data = sql.ExecuteReader())
                {
                    if (data.Read())
                    {
                        id = (int)data["Id"];
                    }
                }
                conn.Close();
            }
            return id;
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
