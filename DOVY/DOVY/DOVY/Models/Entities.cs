using System;
using System.Data.Entity;
using System.Data.Entity.Infrastructure;
using System.Data.Entity.Core.Objects;
using System.Linq;
using System.Data.SqlClient;
using System.Data;
using System.Windows;

namespace DOVY.Models
{


    public partial class Entities : DbContext
    {
        public Entities()
            : base(@"Data Source=(LocalDB)\MSSQLLocalDB;AttachDbFilename=C:\Users\alesk\OneDrive\Dokumenty\GitHub\SchoolUP\DOVY\DOVY\DOVY\DOVY.mdf;Integrated Security=True")
        {
        }

        public virtual DbSet<Meal> Meals { get; set; }
        public virtual DbSet<MealConsistsOf> MealConsistsOfs { get; set; }
        public virtual DbSet<Menu> Menus { get; set; }
        public virtual DbSet<User> Users { get; set; }
        public virtual DbSet<Warehouse> Warehouses { get; set; }
        public virtual DbSet<Ingredient> Ingredients { get; set; }
        public virtual DbSet<MenuView> MenuViews { get; set; }
        public virtual DbSet<Order> Orders { get; set; }
        public virtual DbSet<IngredientByDate> IngredientAmountReqByDates { get; set; }

        public int ValidateCredentials(string username, string password)
        {
            var id = -1;
            foreach(var user in this.Users)
            {
                if (user.UserName == username && user.Password == password)
                {
                    return user.Id;
                } 
            }
            return id;
        }

    }
}
