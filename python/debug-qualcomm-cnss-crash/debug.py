# find memory allocated for cnss and nss drivers and log whether we failed to boot and the memory diff
file = open("qualcomm.log", "r")

line_number = 0
nss_sdma_count=0

cnss_string="Platform driver probed successfully."
nss_sdma_string="set sdma"
crash_string="Internal error"
crash_found=False

cnss_memory=0
nss_sdma1=0
nss_sdma2=0

# Loop through the file line by line
for line in file:

    # checking string is present in line or not
    if cnss_string in line:
        if crash_found:
            crash_found=False
        if not crash_found and nss_sdma1 != 0 and nss_sdma2 != 0:
            #print(f"works cnss={cnss_memory} sdma1={nss_sdma1} sdma2={nss_sdma2}")
            print(f"works diff1={cnss_memory-nss_sdma1}, diff2={cnss_memory-nss_sdma2}")
        cnss_memory=0
        nss_sdma1=0
        nss_sdma2=0
        cnss_memory=int(line[100:110], 16)

    if nss_sdma_string in line:
        sdma = int(line[70:80], 16)

        if nss_sdma1 == 0:
            nss_sdma1=sdma
        else:
            nss_sdma2=sdma

    if crash_string in line:
        #print(f"crash cnss={cnss_memory} sdma1={nss_sdma1} sdma2={nss_sdma2} diff={cnss_memory-nss_sdma1}")
        print(f"crash diff1={cnss_memory-nss_sdma1}, diff2={cnss_memory-nss_sdma2}")
        crash_found=True
        cnss_memory=0
        nss_sdma1=0
        nss_sdma2=0

# closing log file
file.close()
