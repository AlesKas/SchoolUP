using HW8.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace HW8.Controllers
{
    public class BaseController : Controller
    {
        protected UniversityContext Ctx { get; set; }
        public BaseController()
        {
            Ctx = new UniversityContext();
        }
    }
}