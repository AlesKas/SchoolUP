using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.SqlClient;

namespace HW6
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                using (SqlConnection conn = new SqlConnection(@"Data Source=(LocalDB)\MSSQLLocalDB;AttachDbFilename=C:\Users\Aleš\Documents\GitHub\SchoolDesktop\C#\HW6\HW6\db.mdf;Integrated Security=True;Connect Timeout=30"))
                {
                    conn.Open();

                    SqlCommand command = new SqlCommand("SELECT  DISTINCT Jmeno, Prijmeni FROM students ORDER BY Prijmeni OFFSET 5 ROWS FETCH NEXT 10 ROWS ONLY; ", conn);
                    using (SqlDataReader dr = command.ExecuteReader())
                    {
                        while (dr.Read())
                        {
                            Console.WriteLine($"{dr[0]} {dr[1]}");
                        }
                    }
                    Console.WriteLine("------------");

                    SqlCommand add = new SqlCommand("INSERT INTO students (OsCislo, Jmeno, Prijmeni, UserName, Rocnik, OborKomb) VALUES (@OsCislo, @Jmeno, @Prijmeni, @UserName, @Rocnik, @OborKomb);", conn);
                    add.Parameters.Add(new SqlParameter("OsCislo", "R007"));
                    add.Parameters.Add(new SqlParameter("Jmeno", "James"));
                    add.Parameters.Add(new SqlParameter("Prijmeni", "Bond"));
                    add.Parameters.Add(new SqlParameter("UserName", "JB7"));
                    add.Parameters.Add(new SqlParameter("Rocnik", 12));
                    add.Parameters.Add(new SqlParameter("OborKomb", "APLINF"));
                    int aff = add.ExecuteNonQuery();
                    Console.WriteLine($"Affected after adding: {aff}");

                    SqlCommand add2 = new SqlCommand("INSERT INTO students (OsCislo, Jmeno, Prijmeni, UserName, Rocnik, OborKomb) VALUES (@OsCislo, @Jmeno, @Prijmeni, @UserName, @Rocnik, @OborKomb);", conn);
                    add2.Parameters.Add(new SqlParameter("OsCislo", "R17002"));
                    add2.Parameters.Add(new SqlParameter("Jmeno", "Karel"));
                    add2.Parameters.Add(new SqlParameter("Prijmeni", "Řízek"));
                    add2.Parameters.Add(new SqlParameter("UserName", "řízkka02"));
                    add2.Parameters.Add(new SqlParameter("Rocnik", 3));
                    add2.Parameters.Add(new SqlParameter("OborKomb", "APLINF"));
                    int aff2 = add2.ExecuteNonQuery();
                    Console.WriteLine($"Affected after adding: {aff2}");

                    SqlCommand del = new SqlCommand("DELETE FROM students WHERE OborKomb=@obr;", conn);
                    del.Parameters.Add(new SqlParameter("obr", "INF"));
                    int aff3 = del.ExecuteNonQuery();
                    Console.WriteLine($"Affected after deleting: {aff3}");

                    SqlCommand update = new SqlCommand("UPDATE students SET Username=@newName WHERE OsCislo=@param", conn);
                    update.Parameters.Add(new SqlParameter("@param", "R17740"));
                    update.Parameters.Add(new SqlParameter("@newName", "pifkma01"));
                    int aff4 = update.ExecuteNonQuery();
                    Console.WriteLine($"Affected after updating: {aff4}");

                    Console.WriteLine("------------");

                    SqlCommand znamky = new SqlCommand("SELECT * FROM students, exams WHERE students.OsCislo=exams.StudentOsCislo;", conn);
                    using (SqlDataReader drz = znamky.ExecuteReader())
                    {
                        while (drz.Read())
                        {
                            Console.WriteLine($" {drz[1]} {drz[2]}: predmet {drz[6]}, znamka {drz[8]}");
                        }
                    }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
            Console.ReadLine();
        }

    }
}
 