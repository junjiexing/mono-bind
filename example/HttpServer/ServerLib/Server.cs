using System;
using Nancy.Hosting.Self;

namespace ServerLib
{
    public class Server
    {
        private readonly NancyHost _host;
        public Server()
        {
            _host = new NancyHost(
                new HostConfiguration()
                {
                    UrlReservations = new UrlReservations() { CreateAutomatically = true }
                },
                new Uri("http://127.0.0.1:8890/"));
        }
        
        public void Start() => _host.Start();

        public void Stop() => _host.Stop();

    }
}
