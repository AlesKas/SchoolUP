using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Web;

namespace WebAPI.Models
{
    public class ProductContext : DbContext
    {
        public ProductContext() : base("dbo")
        {

        }
        public DbSet<Product> Products { get; set; }
    }
}