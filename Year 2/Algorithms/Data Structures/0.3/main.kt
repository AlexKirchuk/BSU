import java.io.File
import java.io.PrintWriter

fun main()
{
    val fin = File("input.txt")
    val fout = File("output.txt")

    var n = fin.readText().trim().toLong()
    var i = 0L

    val out = PrintWriter(fout)
    while (n != 0L)
    {
        if (n % 2L == 1L)
        {
            out.println(i)
        }
        i++
        n /= 2
    }
    out.close()
}