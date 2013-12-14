import sqlite3 as lite
import sys, os, binascii
from optparse import OptionParser

TABLE_NAME = "files"

def store_to_db(db, path, key, ignore):
	for i in ignore:
		if i in path:
			#print("ignoring file: {0}".format(path))
			return
	print(path + " as '" + key + "'")
	blob = open(path, 'rb')
	data = blob.read();
	blob.close()
	cmd = "INSERT INTO {0} (path, data) VALUES('{1}', ?);".format(TABLE_NAME, key, data)
	#print(cmd)
	#print((lite.Binary(data)))
	db.execute(cmd, [lite.Binary(data)])

def walk_all_files(db, path_global, path_local, fun, ignore):
	for f in os.listdir(os.path.join(path_global, path_local)):
		target_local = os.path.join(path_local, f)
		target_global = os.path.join(path_global, target_local)
		if(os.path.isdir(target_global)):
			walk_all_files(db, path_global, target_local, fun, ignore)
		else:
			fun(db, target_global, target_local, ignore);

con = None

def main(a):
	parser = OptionParser()
	
	parser.add_option("-o", "--outfile", dest="database", help="sets output database file")
	parser.add_option("-f", "--folder", dest="folder", help="sets input directory to be stored in database")
	parser.add_option("-r", "--ignore", dest="ignore", help="sets ignore mask.  Usage: --ignore '.db/.pyc/.log'")
	(arguments, args) = parser.parse_args()

	if arguments.database == None:
		print("Error. parameter --database is not specified. Usage: --database asset.db")
		return
	if arguments.folder == None:
		print("Error. parameter --folder is not specified. Usage: --folder ..\\export")
		return

	if arguments.ignore == None:
		ignore_mask = []
	else:
		ignore_mask = arguments.ignore.split("/")

	try:
		os.remove(arguments.database)
	except:
		None

	print("\n******************************************")
	print("Start packing data to file {0}".format(arguments.database))
	print("******************************************\n")
	con = lite.connect(arguments.database)
	cur = con.cursor()
	cur.execute("CREATE TABLE files(path TEXT, data BLOB, PRIMARY KEY(path)) ;")
	walk_all_files(cur, arguments.folder, "", store_to_db, ignore_mask)
	con.commit()
	con.close()
	print("\n******************************************")
	print("Done packing data")
	print("******************************************\n")

if __name__ == '__main__':
	main(sys.argv)
