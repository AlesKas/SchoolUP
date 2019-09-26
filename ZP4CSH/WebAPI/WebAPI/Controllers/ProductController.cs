using Microsoft.AspNet.OData;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;
using WebAPI.Models;

namespace WebAPI.Controllers
{
    public class ProductController : ODataController
    {
        protected ProductContext Ctx = new ProductContext();

        [EnableQuery]
        public IQueryable<Product> Get()
        {
            return Ctx.Products;
        }

        [EnableQuery]
        public IEnumerable<Product> Get(string contains)
        {
            return Ctx.Products.Where(p => p.Name.Contains(contains));
        }

        [EnableQuery]
        public SingleResult<Product> Get([FromODataUri] int id)
        {
            IQueryable<Product> result = Ctx.Products.Where(p => p.Id == id);
            return SingleResult.Create(result);
        }
    }
}
