from process_monitor import process_mem_usage


#dummy code to fill up some memory
list = ["string" + str(i) for i in range(1024 ** 2)]


process_mem_usage()