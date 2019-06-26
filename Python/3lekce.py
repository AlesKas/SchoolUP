import collections
import sys

ID, FORENAME, MIDDLENAME, SURENAME, DEPARTMENT = range(5)
User = collections.namedtuple("User", 
            "username forename middlename surename id")

def main():

    usernames = set()
    users = {}
    filename = "C:\\Users\\Aleš\\Documents\\GitHub\\SchoolUP\\Python\\data\\users.txt"
    for line in open(filename, encoding="utf8"):
        line = line.rstrip()
        if line:
            user = process_line(line, usernames)
            users[(user.surename.lower(), user.forename.lower(), user.id)] = user
    print_users(users)

def process_line(line, usernames):
    fields = line.split(":")
    username = generate_username(fields, usernames)
    user = User(username, fields[FORENAME], fields[MIDDLENAME],
                fields[SURENAME], fields[ID])
    return user


def generate_username(fields, usernames):
    username = ((fields[FORENAME][0] + fields[MIDDLENAME][:1] +
                 fields[SURENAME]).replace("-", "").replace("'", ""))
    username = original_name = username[:8].lower()
    count = 1
    while username in usernames:
        username = "{0}{1}".format(original_name, count)
        count += 1
    usernames.add(username)
    return username


def print_users(users):
    namewidth = 40
    usernamewidth = 9

    print("{0:<{nw}} {1:^6} {2:{uw}}".format(
          "Jméno", "ID", "Uživ. jm.", nw=namewidth, uw=usernamewidth))
    print("{0:-<{nw}} {0:-<6} {0:-<{uw}}".format(
          "", nw=namewidth, uw=usernamewidth))

    for key in sorted(users):
        user = users[key]
        initial = ""
        if user.middlename:
            initial = " " + user.middlename[0]
        name = "{0.surename}, {0.forename}{1}".format(user, initial)
        print("{0:.<{nw}} ({1.id:4}) {1.username:{uw}}".format(
              name, user, nw=namewidth, uw=usernamewidth))


main()
