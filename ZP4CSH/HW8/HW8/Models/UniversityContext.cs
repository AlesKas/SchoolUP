using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Web;

namespace HW8.Models
{
    public class UniversityContext : DbContext
    {
        public UniversityContext() : base("UniversityConnection")
        {

        }

        public DbSet<Student> Students { get; set; }
        public DbSet<Address> Addresses { get; set; }
        public DbSet<Subject> Subjects { get; set; }
        

        protected override void OnModelCreating(DbModelBuilder mb)
        {
            mb.Entity<Student>().Property(p => p.Surname).IsRequired().HasMaxLength(100);
            mb.Entity<Student>().Property(p => p.Name).IsRequired().HasMaxLength(100);
            mb.Entity<Student>().HasMany(s => s.Subjects).WithMany(s => s.Students);
        }
    }
}