using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HW7
{
    class Students : DbContext
    {
        public Students(string conn) : base(conn) { }
        public DbSet<StudentPredmetu> StudentsSet { get; set; } 
    }
}
