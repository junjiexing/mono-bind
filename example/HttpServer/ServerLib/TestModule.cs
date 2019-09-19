using Nancy;


namespace ServerLib
{
    public class TestModule : NancyModule
    {
        public TestModule()
        {
            Get["/"] = args => Response.AsJson(new { url = Request.Url.ToString() });
        }
    }
}
