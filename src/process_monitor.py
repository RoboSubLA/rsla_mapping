import os, psutil

#how to use
# 1. import me "from process_monitor import process_mem_usage"
# 2. call "process_mem_usage()"" whenever
# 3. awsomesauce

def process_mem_usage():
    process = psutil.Process()
    print("Using:", process.memory_info().rss / 1024 ** 2, "MB")