CURR_PATH=$(shell pwd)
LIB=$(CURR_PATH)/../lib
INCLUDE=-I$(LIB)/include
MYSQL_LIB=-L$(LIB)/lib -lmysqlclient
cc=g++
.PHONY:all,out
all:insert_cgi select_cgi 
insert_cgi:insert_cgi.cpp comm.cpp
	g++ -o $@ $^ $(INCLUDE) $(MYSQL_LIB)
select_cgi:select_cgi.cpp comm.cpp
	g++ -o $@ $^ $(INCLUDE) $(MYSQL_LIB)
out:
	cp insert_cgi ../wwwroot/cgi
	cp select_cgi ../wwwroot/cgi
	mv name_cgi ../wwwroot/cgi
.PHONY:clean
clean:
	rm -f insert_cgi select_cgi 


