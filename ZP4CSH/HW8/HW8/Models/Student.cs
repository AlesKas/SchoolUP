using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace HW8.Models
{
    public class Student
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public string Surname { get; set; }
        public int Rocnik { get; set; }
        public virtual Address Address { get; set; }
        private ICollection<Subject> subjects;
        public virtual ICollection<Subject> Subjects
        {
            get { return subjects ?? (subjects = new HashSet<Subject>()); }
            set { subjects = value; }
        }
    }
}