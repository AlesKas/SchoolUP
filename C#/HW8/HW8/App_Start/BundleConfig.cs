using System.Web;
using System.Web.Optimization;

namespace HW8
{
    public class BundleConfig
    {
        // Další informace o sdružování najdete na webu https://go.microsoft.com/fwlink/?LinkId=301862.
        public static void RegisterBundles(BundleCollection bundles)
        {
            bundles.Add(new ScriptBundle("~/bundles/jquery").Include(
                        "~/Scripts/jquery-{version}.js"));

            bundles.Add(new ScriptBundle("~/bundles/jqueryval").Include(
                        "~/Scripts/jquery.validate*"));

            // Použijte k vývoji a k získání informací vývojovou verzi produktu Modernizr. Až budete
            // Připraveno na produkční prostředí. Použijte nástroj pro sestavení na webu https://modernizr.com a vyberte jenom testy, které potřebujete.
            bundles.Add(new ScriptBundle("~/bundles/modernizr").Include(
                        "~/Scripts/modernizr-*"));

            bundles.Add(new ScriptBundle("~/bundles/bootstrap").Include(
                      "~/Scripts/bootstrap.js"));

            bundles.Add(new StyleBundle("~/Content/css").Include(
                      "~/Content/bootstrap.css",
                      "~/Content/site.css"));
        }
    }
}
