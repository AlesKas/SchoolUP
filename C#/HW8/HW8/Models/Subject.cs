using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace HW8.Models
{
    public class Subject
    {
        public int Id { get; set; }
        public string Abbrev { get; set; }
        public string Department { get; set; }
        public string Name { get; set; }

        private ICollection<Student> students;
        public virtual ICollection<Student> Students
        {
            get { return students ?? (students = new HashSet<Student>()); }
            set { students = value; }
        }
    }
}