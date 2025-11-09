var
  fin, fout: Text;
  n, i: Int64;
begin
  Assign(fin, 'input.txt');
  Reset(fin);
  Assign(fout, 'output.txt');
  Rewrite(fout);

  Read(fin, n);
  i := 0;

  while n <> 0 do
  begin
    if (n mod 2 = 1) then
      Writeln(fout, i);
    Inc(i);
    n := n div 2;
  end;

  Close(fin);
  Close(fout);
end.