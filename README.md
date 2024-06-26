# Group Password Generator

This project is a command-line application that employs multithreading to populate a hash set with words from a specified .txt file, referred to as a Dictionary. Subsequently, it leverages multithreading to access the previously mentioned hash set and generate a series of random passwords.

## Required Flags

* -f file: specifies the name of the dictionary file. Note that a dictionary has been provided under the folder `Data`.

* -p n: specifies the number(n) of threads that will be used to grab words from the provided file and put them in the hash set.

* -c m:specifies the number(m) of consumer threads.

* -n k: specifies the number of passwords that the program must generate. Note that k should be divisible by m.

* -l l: specifies the number of words per password.

## Example

Shell command(Windows):
```
.\passgenerator.exe -p 5 -c 5 -f "Data/dict.txt" -n 10 -l 5
```
Shell command(Unix):
```
./passgenerator -p 5 -c 5 -f "Data/dict.txt" -n 10 -l 5
```
Output:
```
abactinalconstituentatriplicifoliumedentulatecorporis
choriomeningitisbronchoscopeexpatiateelegiacdisorient
acceptablyambitiousnessbunionappositionarmillaria
asafoetidaepisomedeviltryco-workerbloomsbury
creasedroopeaterycocuswoodblocked
cacklycolubrisconundrumcoxcrazyweed
armisticeddschalumnaebrown-greyagone
ethnicallydilly-dallyflare-upfeathertopcommunise
fourhandedceruminousankletsabiogenesisabsconder
apomicticalchefbarcarolleequisetalesavitaminosis
```

## Need to recompile?

This project provides the command `passgenerator` for Unix development environments and the command `passgenerator.exe` for Windows development environments. However, if there is a need to recompile, the flags "-lm" and "-pthread" must be used.
* Note that this program provides files to recompile that already have these flags.
  * If the coding environment is Unix-based, you can use the `makefile`.
  * If the coding environment is Windows-based, you can use `.vscode\tasks.json` in combination with VScode to recompile.
