LD_TRACE_LOADED_OBJECTS=1 $1
#utils

dyld && man dyld
otool -L
DYLD_PRINT_BINDINGS=1 DYLD_PREBIND_DEBUG=1 DYLD_PRINT_INITIALIZERS=1 DYLD_PRINT_APIS=1 DYLD_PRINT_LIBRARIES=1 DYLD_PRINT_RPATHS=1
install_name_tool


###########################################
# How to Fix library dependencies problem
###########################################
cd /Users/enrique/projects/qtrader/bin
cp /usr/local/mysql/lib/libmysqlclient.21.dylib .
# tell libqsqlmysql.dylib the path where its dependency (libmysqlclient.21.dylib) will be searched
install_name_tool -change @rpath/libmysqlclient.21.dylib @executable_path/libmysqlclient.21.dylib /Users/enrique/Qt/5.13.0/clang_64/plugins/sqldrivers/libqsqlmysql.dylib
cp /Users/enrique/Qt/Qt\ Creator.app/Contents/Frameworks/libcrypto.1.0.0.dylib .
cp /Users/enrique/Qt/Qt\ Creator.app/Contents/Frameworks/libssl.1.0.0.dylib .
