#!/usr/bin/pyhton3
from random import randbytes
import filecmp
import os

def print_red(string): print("\033[91m{}\033[00m" .format(string))
def print_green(string): print("\033[92m{}\033[00m" .format(string))
def print_gray(string): print("\033[97m{}\033[00m" .format(string))
def print_black(string): print("\033[98m{}\033[00m" .format(string))
def print_yellow(string): print("\033[93m{}\033[00m" .format(string))
 
# Configuration
my_whirlpool_cmd = "./ft_ssl whirlpool "
my_md5_cmd = "./ft_ssl md5 "
my_sha256_cmd = "./ft_ssl sha256 "
my_sha512_cmd = "./ft_ssl sha512 "
my_output = "/tmp/sys_out"

temporary_file = "ssl_test.txt"

sys_whirlpool_cmd = "openssl whirlpool "
sys_md5_cmd = "openssl md5 "
sys_sha256_cmd = "openssl sha256 "
sys_sha512_cmd = "openssl sha512 "
sys_output = "/tmp/my_out"

# Constant definitions
block_size = 64
block_size_sha512 = 128

#CHANGE FOR DIFFERENT ALGORITHMS ex : md5 32, sha256 64, sha512 128
#TODO : TESTER TOUTES LES COMBINAISONS D'OPTIONS
# Utils
def generate_file(length):
    tmp_file = open(temporary_file, "wb")
    content = randbytes(length)
    tmp_file.write(content)
    return tmp_file

def check_hash(algo):
    if algo == "whirlpool":
        os.system(my_whirlpool_cmd + " " + temporary_file + " > " + my_output)
        os.system(sys_whirlpool_cmd + " " + temporary_file + " > " + sys_output)
        ret = filecmp.cmp(my_output, sys_output, shallow="False")
        if ret == False:
            os.system("cp " + temporary_file + " /tmp/last_error.txt")
        return ret
    elif algo == "md5":
        os.system(my_md5_cmd + " " + temporary_file + " > " + my_output)
        os.system(sys_md5_cmd + " " + temporary_file + " > " + sys_output)
        ret = filecmp.cmp(my_output, sys_output, shallow="False")
        if ret == False:
            os.system("cp " + temporary_file + " /tmp/last_error.txt")
        return ret
    elif algo == "sha256":
        os.system(my_sha256_cmd + " " + temporary_file + " > " + my_output)
        os.system(sys_sha256_cmd + " " + temporary_file + " > " + sys_output)
        ret = filecmp.cmp(my_output, sys_output, shallow="False")
        if ret == False:
            os.system("cp " + temporary_file + " /tmp/last_error.txt")
        return ret
    elif algo == "sha512":
        os.system(my_sha512_cmd + " " + temporary_file + " > " + my_output)
        os.system(sys_sha512_cmd + " " + temporary_file + " > " + sys_output)
        ret = filecmp.cmp(my_output, sys_output, shallow="False")
        if ret == False:
            os.system("cp " + temporary_file + " /tmp/last_error.txt")
        return ret

# Testing around block size
err_count = 0;

####################################################################################################
#                            Testing file whith empty file                                         #
####################################################################################################

print_yellow("\u256D" + " " * 46 + "\u256E")
print_yellow(" " * 15 + " Testting empty file ")
print_yellow("\u2570" + " " * 46 + "\u256F")

empty = open(temporary_file, "w")
if check_hash("md5") == False:
    print_red("\U0001F7E5" + " MD5 : Error on an empty file, please check \"/tmp/empty.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/empty.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "MD5 : Successfully handled with empty file.")
if check_hash("sha256") == False:
    print_red("\U0001F7E5" + " SHA256 : Error on an empty file, please check \"/tmp/empty.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/empty.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "SHA256 : Successfully handled with empty file.")
if check_hash("whirlpool") == False:
    print_red("\U0001F7E5" + " WHIRLPOOL : Error on an empty file, please check \"/tmp/empty.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/empty.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "WHIRLPOOL : Successfully handled with empty file.")
if check_hash("sha512") == False:
    print_red("\U0001F7E5" + " SHA512 : Error on an empty file, please check \"/tmp/empty.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/empty.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "SHA512 : Successfully handled with empty file.")
empty.close()

####################################################################################################
#                               Testing file whith 1 byte                                          #
####################################################################################################

print_yellow("\n\n\u256D" + " " * 46 + "\u256E")
print_yellow(" " * 12 + " Testting file whith 1 byte ")
print_yellow("\u2570" + " " * 46 + "\u256F")

single_char = generate_file(1)
if check_hash("md5") == False:
    print_red("\U0001F7E5" + " MD5 : Error on single byte, please check \"/tmp/single_byte.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/single_byte.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "MD5 : Successfully handled with single byte.")
if check_hash("sha256") == False:
    print_red("\U0001F7E5" + " SHA256 : Error on single byte, please check \"/tmp/single_byte.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/single_byte.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "SHA256 : Successfully handled with single byte.")
if check_hash("whirlpool") == False:
    print_red("\U0001F7E5" + " WHIRLPOOL : Error on single byte, please check \"/tmp/single_byte.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/single_byte.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "WHIRLPOOL : Successfully handled with single byte.")
if check_hash("sha512") == False:
    print_red("\U0001F7E5" + " SHA512 : Error on single byte, please check \"/tmp/single_byte.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/single_byte.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "SHA512 : Successfully handled with single byte.")
single_char.close()


####################################################################################################
#                               Testing file whith block_size/2                                    #
####################################################################################################

print_yellow("\n\n\u256D" + " " * 46 + "\u256E")
print_yellow(" " * 5 + " Testting file whith block_size/2 bytes ")
print_yellow("\u2570" + " " * 46 + "\u256F")

half_block = generate_file(int(block_size/2))
if check_hash("md5") == False:
    print_red("\U0001F7E5" + " MD5 : Error on a 32 bytes file, please check \"/tmp/half_block.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/half_block.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "MD5 : Successfully handled a randomly generated 32 bytes file.")
if check_hash("sha256") == False:
    print_red("\U0001F7E5" + " SHA256 : Error on a 32 bytes file, please check \"/tmp/half_block.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/half_block.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "SHA256 : Successfully handled a randomly generated 32 bytes file.")
if check_hash("whirlpool") == False:
    print_red("\U0001F7E5" + " WHIRLPOOL : Error on a 32 bytes file, please check \"/tmp/half_block.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/half_block.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "WHIRLPOOL : Successfully handled a randomly generated 32 bytes file.")
half_block.close()
half_blockSHA = generate_file(int(block_size_sha512/2))
if check_hash("sha512") == False:
    print_red("\U0001F7E5" + " SHA512 : Error on a 64 bytes file, please check \"/tmp/half_block.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/half_block.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "SHA512 : Successfully handled a randomly generated 64 bytes file.")
half_blockSHA.close()


####################################################################################################
#                               Testing file whith block_size                                      #
####################################################################################################

print_yellow("\n\n\u256D" + " " * 46 + "\u256E")
print_yellow(" " * 5 + " Testting file whith block_size bytes ")
print_yellow("\u2570" + " " * 46 + "\u256F")

single_block = generate_file(block_size)
if check_hash("md5") == False:
    print_red("\U0001F7E5" + " MD5 : Error on a 64 bytes file, please check \"/tmp/single_block.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/single_block.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "MD5 : Successfully handled a randomly generated 64 bytes file.")
if check_hash("sha256") == False:
    print_red("\U0001F7E5" + " SHA256 : Error on a 64 bytes file, please check \"/tmp/single_block.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/single_block.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "SHA256 : Successfully handled a randomly generated 64 bytes file.")
if check_hash("whirlpool") == False:
    print_red("\U0001F7E5" + " WHIRLPOOL : Error on a 64 bytes file, please check \"/tmp/single_block.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/single_block.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "WHIRLPOOL : Successfully handled a randomly generated 64 bytes file.")
single_block.close()
single_blockSHA = generate_file(block_size_sha512)
if check_hash("sha512") == False:
    print_red("\U0001F7E5" + " SHA512 : Error on a 128 bytes file, please check \"/tmp/single_block.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/single_block.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "SHA512 : Successfully handled a randomly generated 128 bytes file.")
single_blockSHA.close()


####################################################################################################
#                               Testing file whith block_size*2                                    #
####################################################################################################
print_yellow("\n\n\u256D" + " " * 46 + "\u256E")
print_yellow(" " * 5 + " Testting file whith block_size*2 bytes ")
print_yellow("\u2570" + " " * 46 + "\u256F")

two_blocks = generate_file(block_size*2)
if check_hash("md5") == False:
    print_red("\U0001F7E5" + " MD5 : Error on a 128 bytes file, please check \"/tmp/two_blocks.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/two_blocks.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "MD5 : Successfully handled a randomly generated 128 bytes file.")
if check_hash("sha256") == False:
    print_red("\U0001F7E5" + " SHA256 : Error on a 128 bytes file, please check \"/tmp/two_blocks.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/two_blocks.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "SHA256 : Successfully handled a randomly generated 128 bytes file.")
if check_hash("whirlpool") == False:
    print_red("\U0001F7E5" + " WHIRLPOOL : Error on a 128 bytes file, please check \"/tmp/two_blocks.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/two_blocks.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "WHIRLPOOL : Successfully handled a randomly generated 128 bytes file.")
two_blocks.close()
two_blocksSHA = generate_file(block_size_sha512*2)
if check_hash("sha512") == False:
    print_red("\U0001F7E5" + " SHA512 : Error on a 256 bytes file, please check \"/tmp/two_blocks.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/two_blocks.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "SHA512 : Successfully handled a randomly generated 256 bytes file.")
two_blocksSHA.close()


####################################################################################################
#                               Testing file whith block_size-1                                    #
####################################################################################################

print_yellow("\n\n\u256D" + " " * 46 + "\u256E")
print_yellow(" " * 5 + " Testting file whith block_size-1 bytes ")
print_yellow("\u2570" + " " * 46 + "\u256F")

block_minus_one = generate_file(block_size-1)
if check_hash("md5") == False:
    print_red("\U0001F7E5" + " MD5 : Error on a 63 bytes file, please check \"/tmp/block_minus_one.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/block_minus_one.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "MD5 : Successfully handled a randomly generated 63 bytes file.")
if check_hash("sha256") == False:
    print_red("\U0001F7E5" + " SHA256 : Error on a 63 bytes file, please check \"/tmp/block_minus_one.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/block_minus_one.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "SHA256 : Successfully handled a randomly generated 63 bytes file.")
if check_hash("whirlpool") == False:
    print_red("\U0001F7E5" + " WHIRLPOOL : Error on a 63 bytes file, please check \"/tmp/block_minus_one.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/block_minus_one.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "WHIRLPOOL : Successfully handled a randomly generated 63 bytes file.")
block_minus_one.close()
block_minus_oneSHA = generate_file(block_size_sha512-1)
if check_hash("sha512") == False:
    print_red("\U0001F7E5" + " SHA512 : Error on a 127 bytes file, please check \"/tmp/block_minus_one.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/block_minus_one.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "SHA512 : Successfully handled a randomly generated 127 bytes file.")
block_minus_oneSHA.close()


####################################################################################################
#                               Testing file whith block_size-2                                    #
####################################################################################################

print_yellow("\n\n\u256D" + " " * 46 + "\u256E")
print_yellow(" " * 5 + " Testting file whith block_size-2 bytes ")
print_yellow("\u2570" + " " * 46 + "\u256F")

block_minus_two = generate_file(block_size-2)
if check_hash("md5") == False:
    print_red("\U0001F7E5" + " MD5 : Error on a 62 bytes file, please check \"/tmp/block_minus_two.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/block_minus_two.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "MD5 : Successfully handled a randomly generated 62 bytes file.")
if check_hash("sha256") == False:
    print_red("\U0001F7E5" + " SHA256 : Error on a 62 bytes file, please check \"/tmp/block_minus_two.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/block_minus_two.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "SHA256 : Successfully handled a randomly generated 62 bytes file.")
if check_hash("whirlpool") == False:
    print_red("\U0001F7E5" + " WHIRLPOOL : Error on a 62 bytes file, please check \"/tmp/block_minus_two.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/block_minus_two.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "WHIRLPOOL : Successfully handled a randomly generated 62 bytes file.")
block_minus_two.close()
block_minus_twoSHA = generate_file(block_size_sha512-2)
if check_hash("sha512") == False:
    print_red("\U0001F7E5" + " SHA512 : Error on a 126 bytes file, please check \"/tmp/block_minus_two.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/block_minus_two.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "SHA512 : Successfully handled a randomly generated 126 bytes file.")
block_minus_twoSHA.close()


####################################################################################################
#                           Testing file whith block_size + 1 bytes                                #
####################################################################################################

print_yellow("\n\n\u256D" + " " * 46 + "\u256E")
print_yellow(" " * 5 + " Testting file whith block_size + 1 bytes ")
print_yellow("\u2570" + " " * 46 + "\u256F")

block_plus_one = generate_file(block_size+1)
if check_hash("md5") == False:
    print_red("\U0001F7E5" + " MD5 : Error on a 65 bytes file, please check \"/tmp/block_plus_one.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/block_plus_one.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "MD5 : Successfully handled a randomly generated 65 bytes file.")
if check_hash("sha256") == False:
    print_red("\U0001F7E5" + " SHA256 : Error on a 65 bytes file, please check \"/tmp/block_plus_one.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/block_plus_one.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "SHA256 : Successfully handled a randomly generated 65 bytes file.")
if check_hash("whirlpool") == False:
    print_red("\U0001F7E5" + " WHIRLPOOL : Error on a 65 bytes file, please check \"/tmp/block_plus_one.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/block_plus_one.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "WHIRLPOOL : Successfully handled a randomly generated 65 bytes file.")
block_plus_one.close()
block_plus_oneSHA = generate_file(block_size_sha512+1)
if check_hash("sha512") == False:
    print_red("\U0001F7E5" + " SHA512 : Error on a 129 bytes file, please check \"/tmp/block_plus_one.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/block_plus_one.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "SHA512 : Successfully handled a randomly generated 129 bytes file.")
block_plus_oneSHA.close()

####################################################################################################
#                           Testing file whith block_size + 2 bytes                                #
####################################################################################################

print_yellow("\n\n\u256D" + " " * 46 + "\u256E")
print_yellow(" " * 5 + " Testting file whith block_size + 2 bytes ")
print_yellow("\u2570" + " " * 46 + "\u256F")

block_plus_two = generate_file(block_size+2)
if check_hash("md5") == False:
    print_red("\U0001F7E5" + " MD5 : Error on a 66 bytes file, please check \"/tmp/block_plus_two.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/block_plus_two.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "MD5 : Successfully handled a randomly generated 66 bytes file.")
if check_hash("sha256") == False:
    print_red("\U0001F7E5" + " SHA256 : Error on a 66 bytes file, please check \"/tmp/block_plus_two.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/block_plus_two.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "SHA256 : Successfully handled a randomly generated 66 bytes file.")
if check_hash("whirlpool") == False:
    print_red("\U0001F7E5" + " WHIRLPOOL : Error on a 66 bytes file, please check \"/tmp/block_plus_two.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/block_plus_two.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "WHIRLPOOL : Successfully handled a randomly generated 66 bytes file.")
block_plus_two.close()
block_plus_twoSHA = generate_file(block_size_sha512+2)
if check_hash("sha512") == False:
    print_red("\U0001F7E5" + " SHA512 : Error on a 130 bytes file, please check \"/tmp/block_plus_two.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/block_plus_two.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "SHA512 : Successfully handled a randomly generated 130 bytes file.")
block_plus_twoSHA.close()

####################################################################################################
#                           Testing file whith big file                                            #
####################################################################################################

print_yellow("\n\n\u256D" + " " * 46 + "\u256E")
print_yellow(" " * 5 + " Testting file whith big file ")
print_yellow("\u2570" + " " * 46 + "\u256F")

# Testing against big file
print_gray("Creating a 150MB file...")
os.system("dd if=/dev/urandom of=" + temporary_file + " bs=1m count=150")
print_gray("Done.")
if check_hash("md5") == False:
    print_red("\U0001F7E5" + " MD5 : Error on a 150MB file, please check \"/tmp/huge.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/huge.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "MD5 : Successfully handled a randomly generated 150MB file.")
if check_hash("sha256") == False:
    print_red("\U0001F7E5" + " SHA256 : Error on a 150MB file, please check \"/tmp/huge.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/huge.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "SHA256 : Successfully handled a randomly generated 150MB file.")
if check_hash("whirlpool") == False:
    print_red("\U0001F7E5" + " WHIRLPOOL : Error on a 150MB file, please check \"/tmp/huge.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/huge.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "WHIRLPOOL : Successfully handled a randomly generated 150MB file.")
if check_hash("sha512") == False:
    print_red("\U0001F7E5" + " SHA512 : Error on a 150MB file, please check \"/tmp/huge.diff\" for details.")
    os.system("diff " + my_output + " " + sys_output + " > /tmp/huge.diff")
    err_count += 1;
else:
    print_green("\u2705 " + "SHA512 : Successfully handled a randomly generated 150MB file.")
os.system("rm " + temporary_file)
print("")

####################################################################################################
#                       Testing against non-ending file                                            #
####################################################################################################

print_yellow("\n\n\u256D" + " " * 46 + "\u256E")
print_yellow(" " * 5 + " Testting against non-ending file")
print_yellow("\u2570" + " " * 46 + "\u256F")

print_gray("Reading random bytes for 1 minutes and half...")
os.system("timeout 90 " + my_md5_cmd + " /dev/random")
print_green("\u2705 " + "MD5 : Successfully handled against non-ending file.")
print_gray("Reading random bytes for 1 minutes and half...")
os.system("timeout 90 " + my_sha256_cmd + " /dev/random")
print_green("\u2705 " + "SHA256 : Successfully handled against non-ending file.")
print_gray("Reading random bytes for 1 minutes and half...")
os.system("timeout 90 " + my_whirlpool_cmd + " /dev/random")
print_green("\u2705 " + "WHIRLPOOL : Successfully handled against non-ending file.")
print_gray("Reading random bytes for 1 minutes and half...")
os.system("timeout 90 " + my_sha512_cmd + " /dev/random")
print_green("\u2705 " + "SHA512 : Successfully handled against non-ending file.")


####################################################################################################
#                                        CONCLUSION                                                #
####################################################################################################

print("\n\n")
print_yellow("\u256D" + " " * 46 + "\u256E")
print_yellow(" " * 15 + " CONCLUSION ")
print_yellow("\u2570" + " " * 46 + "\u256F")
if err_count > 0:
    print_red("              ｡ﾟ(TヮT)ﾟ｡\n")
    print_red("Not this time, we found " + str(err_count) + " error(s)!")
    print_red("\n             ｡ﾟ(TヮT)ﾟ｡")
else:
    print_green("      ☆*:.｡.o(≧▽≦)o.｡.:*☆\n")
    print_green("No error found, you're good to go!")
    print_green("\n      ☆*:.｡.o(≧▽≦)o.｡.:*☆")
print("")