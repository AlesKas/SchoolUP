using System;
using System.Collections.Generic;
using System.Text;

namespace DOVY.Models
{
    public class User
    {
        public User()
        {
            this.Orders = new HashSet<Order>();
        }

        public int Id { get; set; }
        public string UserName { get; set; }
        public string Password { get; set; }
        public Nullable<System.DateTime> LastLogin { get; set; }
        public string Permission { get; set; }

        public virtual ICollection<Order> Orders { get; set; }
    }
}
