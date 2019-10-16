import sys, mysql.connector as sql
conn=sql.connect(host='localhost',user='root',password='0020',database='mohan')

if conn.is_connected():
    print("Connected")
    cur=conn.cursor()

def printRes():
    print(cur.column_names)
    for row in cur.fetchall(): print(row)


print("\nQuery 1")
cur.execute("select agency,sum(package_amt) as 'revenue' from tourist group by agency;")
printRes()

print("\nQuery 2")
cur.execute("select tourist.name,places.name from tourist,places where tourist.tcode=places.t_code;")
printRes()

print("\nQuery 3")
cur.execute("select count(name) as 'NO.' from places where name like 'A%'")
printRes()

print("\nQuery 4")
cur.execute("select max(package_amt),min(package_amt),sum(package_amt) from tourist;")
printRes()

print("\nQuery 5")
cur.execute("select name from tourist where age in(23,21,26)")
printRes()

print("\nQuery 6")
cur.execute("select tourist.name,tourist.package_amt,places.name from tourist,places where tourist.tcode=places.t_code and tourist.name in ('Hardeep','Kavita','Medha')")
printRes()

print("\nQuery 7")
cur.execute("Select * from tourist order by name desc;")
printRes()

print("\nQuery 8")
cur.execute("update tourist set package_amt=package_amt*1.1")
cur.execute("select * from tourist;")
printRes()
conn.commit()
