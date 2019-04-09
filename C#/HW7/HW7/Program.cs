using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.Xml.Serialization;

namespace HW7
{
    class Program
    {

        static void Main(string[] args)
        {
            string path = @"D:\C#\studentiPredmetu.xml";
            try
            {
                Random num = new Random();
                using (Students st = new Students("StudentsConn"))
                {

                    XmlDocument document = new XmlDocument();
                    document.Load(path);
                    XmlNodeList nodes = document.GetElementsByTagName("studentPredmetu");
                    foreach (XmlNode node in nodes)
                    {
                        StudentPredmetu student = new StudentPredmetu();
                        student.Jmeno = node["jmeno"].InnerText;
                        student.Prijmeni = node["prijmeni"].InnerText;
                        student.OborKomb = node["oborKomb"].InnerText;
                        student.UserName = node["userName"].InnerText;
                        student.OsCislo = node["osCislo"].InnerText;
                        student.Rocnik = node["rocnik"].InnerText;
                        Exam exam = new Exam { Subject = "PAPR1", Grade = num.Next(5) + 1 };
                        student.Exam = exam;
                        st.StudentsSet.Add(student);
                    }
                    st.SaveChanges();

                    var names = st.StudentsSet.Select(p => new { p.Jmeno, p.Prijmeni}).OrderBy(p => p.Prijmeni).Skip(4).Take(10);
                    foreach(var name in names)
                    {
                        Console.WriteLine($"{name.Jmeno} {name.Prijmeni}");
                    }

                    StudentPredmetu bond = new StudentPredmetu() { OsCislo = "R007", Jmeno = "James", Prijmeni = "Bond", OborKomb = "AplInf", Rocnik = "12", UserName = "JB007", Exam = new Exam() { Subject = "PAPR1", Grade = num.Next(5) + 1 } };
                    st.StudentsSet.Add(bond);

                    StudentPredmetu rizek = new StudentPredmetu() { OsCislo = "R17002", Jmeno = "Karel", Prijmeni = "Řízek", OborKomb = "AplInf", Rocnik = "2", UserName = "řízkka02", Exam = new Exam() { Subject = "PAPR1", Grade = num.Next(5) + 1 } };
                    st.StudentsSet.Add(rizek);
                    st.SaveChanges();

                    var toDelete = st.StudentsSet.Where(p => p.OborKomb == "INF");
                    foreach (StudentPredmetu s in toDelete)
                        st.StudentsSet.Remove(s);
                    st.SaveChanges();

                    var pif = st.StudentsSet.Where(p => p.OsCislo == "R17740").ToList().First();
                    pif.UserName = "pifkma01";
                    st.SaveChanges();

                    foreach (StudentPredmetu stud in st.StudentsSet)
                    {
                        Console.WriteLine($"{stud.Jmeno} {stud.Prijmeni}, {stud.Exam.Subject}: {stud.Exam.Grade}");
                    }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }
            Console.ReadLine();
        }
    }
}
