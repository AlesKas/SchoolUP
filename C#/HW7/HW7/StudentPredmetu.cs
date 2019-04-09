using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HW7
{
    class StudentPredmetu
    {
        public int Id { get; set; }
        public string OsCislo { get; set; }
        public string Jmeno { get; set; }
        public string Prijmeni { get; set; }
        public string UserName { get; set; }
        public string Rocnik { get; set; }
        public string OborKomb { get; set; }
        public virtual Exam Exam { get; set; }
    }
}
