using System;
using System.Collections.Generic;
using System.Text;

namespace DOVY.Models
{
    public class Order
    {
        public int Id { get; set; }
        public int UserId { get; set; }
        public int MenuId { get; set; }
        public System.DateTime OrderTime { get; set; }

        public virtual Menu Menu { get; set; }
        public virtual User User { get; set; }
    }
}
