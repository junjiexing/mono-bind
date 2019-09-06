using System;

namespace Example
{
    public class Hello
    {
        public Hello()
        {
            Console.WriteLine("Helloctor");
        }

        ~Hello()
        {
            Console.WriteLine("Hellodtor");
        }
        public void SayHello()
        {
            Console.WriteLine("Hello world from libmono!");
        }
    }
}
