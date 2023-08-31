rsa435 must be ran first. It does not accept any command line arguments.
Upon start, 2 random numbers will be generated, p and q. These will be tested for primality using Fermat's little theorem(FLT). Normally, all values of 'a' would be tested with FLT, but only 2 are randomly selected and tested for this program due to the large size of p and q. If p or q fail the FLT, they are randomly generated again until they pass. Once they both pass, they are outputted to the file 'p_q.txt', overriding any text already present.
p and q are used to find n and phi(n), which is then used to generate e and d.
d and n are stored in the file 'd_n.txt' as the private key.
e and n are stored in the file 'e_n.txt' as the public key.
That is the end of rsa435.
Afterwards, messageDigest435 can be run.
This file requires command line arguments in one of two formats: "a.exe s filename" or "a.exe v filename sigfile".
The first format is for creating a signature from the given file. It will first generate a hash based on the input file and grab the private key from the file created by rsa435. It will then convert the hash from base 16 to base 10 and use the private key to 'sign' the hash, creating the signature. This signature is stored in the file 'file.txt.signature'. 
The second format is used for verifying a file using a signature. It will once again generate a hash based on the input file and convert it to base 10. The signature will be grabbed from the provided file and the public key will be grabbed from the file created by rsa435. The public key will then be used to 'unsign' the signature, and the result will be compared with the converted hash. If they match, the document is authentic, else it has been modified since encryption.
