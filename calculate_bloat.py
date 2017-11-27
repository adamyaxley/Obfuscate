import os, errno, subprocess, sys

def callCommand(command):
    process = subprocess.Popen(command, stdout=subprocess.PIPE)
    process.communicate()
    process.wait()

def main():
    dir = "test_bloat"
    try:
        os.makedirs(dir)
    except OSError as e:
        if e.errno != errno.EEXIST:
            raise
    os.chdir(dir)
    callCommand(["cmake", ".."])
    callCommand(["cmake", "--build", ".", "--config", "Debug"])
    callCommand(["cmake", "--build", ".", "--config", "Release"])
    os.chdir("..")
    
    print ("| Config | Plain string literals | Obfuscated strings | Bloat |")
    print ("|:------:|:---------------------:|:------------------:|:-----:|")
    for config in ["Release", "Debug"]:
        sizeOn = os.stat(os.path.join(dir, config, "obfuscate_test_bloat_on.exe")).st_size
        sizeOff = os.stat(os.path.join(dir, config, "obfuscate_test_bloat_off.exe")).st_size
        print ("| {} | {} | {} | {} ({:.1f}%) |".format(config, sizeOff, sizeOn, sizeOn - sizeOff, (sizeOn / sizeOff - 1.0) * 100))

if __name__ == "__main__":
    main()