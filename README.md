Command-line tool to write RAW 10bit 4:2:2 UYVY Big Endian files from text-defined .ini file.
Usage: WriteTrsnsients.exe <ini_file_name>

[Common]
NumTrans=10 - num transients to read from ini and write
NumLines=50 - num of lines total to write (some software like RawSource pluging looks like to read 8 and more lines). All lines are equal.

[Transient1] - first transient params
LeftY=64 - left sustained Y'CbCr values, all values are decimal. May be up to 65535 if write 16-bit-ranged files.
LeftCb=512
LeftCr=512
LeftSz=48 - runlength of sustained data before transient data starts, must be even.

RightY=414 - right sustained Y'CbCr values
RightCb=512
RightCr=512
RightSz=54 - runlength of sustained data after transient data ends, must be even.

Y01=64 - 10 Y' samples of transient
Y02=64
Y03=64
Y04=73
Y05=198
Y06=358
Y07=406
Y08=414
Y09=414
Y10=414

Cb01=512 - 5 Cb samples of transient (4:2:2 sampled)
Cb02=512
Cb03=512
Cb04=512
Cb05=512

Cr01=512 - 5 Cr samples of transient (4:2:2 sampled)
Cr02=512
Cr03=512
Cr04=512
Cr05=512

Output raw data file line size (in Y' samples) and height (=lines written) in the console output after executable finishes.
