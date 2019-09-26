using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;
using WebAPI.Models;

namespace WebAPI.Controllers
{
    public class BaseController : ApiController
    {
        protected ProductContext Ctx { get; set; }
        public BaseController()
        {
            Ctx = new ProductContext();
        }
    }
}
