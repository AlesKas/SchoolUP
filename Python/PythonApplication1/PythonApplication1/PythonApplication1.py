#pip install pythonnet
import clr
import System
import System.Collections.Generic
import System.IO

System.Console.WriteLine("Simple Python app to test calling C# dlls")

#import managed dll, add reference to namespace 
clr.AddReference('ClassLibrary4')
clr.AddReference('SimpleCMD')
#dont forget to import class from referenced namespace
from ClassLibrary4 import Class1
from SimpleCMD import Class2

print(Class1.hello('python'))

di = System.IO.DirectoryInfo('C')
array = System.Array[System.IO.DriveInfo](System.IO.DriveInfo.GetDrives())
for diInfo in array:
    if diInfo.IsReady:
        total = Class2.GetHumanReadableFileSize(diInfo.TotalSize)
        ava = Class2.GetHumanReadableFileSize(diInfo.AvailableFreeSpace)
        print("{} Total: {} , Free: {}".format(diInfo.Name, total, ava))