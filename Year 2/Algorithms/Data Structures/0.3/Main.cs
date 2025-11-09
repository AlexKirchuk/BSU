using System;
using System.IO;

class Program
{
    static void Main()
    {
        using (StreamReader fin = new StreamReader("input.txt"))
        using (StreamWriter fout = new StreamWriter("output.txt"))
        {
            long n = long.Parse(fin.ReadLine());
            long i = 0;

            while (n != 0)
            {
                if (n % 2 == 1)
                {
                    fout.WriteLine(i);
                }
                i++;
                n /= 2;
            }
        }
    }
}