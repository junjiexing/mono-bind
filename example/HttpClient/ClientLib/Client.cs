using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;

namespace ClientLib
{
    public class Client
    {
        public string Get(string url)
        {
            using(var client = new HttpClient())
            {
                return client.GetStringAsync(url).Result;
            }
        }
    }
}
