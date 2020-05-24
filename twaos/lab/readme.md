Install things:

```bash
apt-get update
apt install python3 python3-pip python3-doc
apt install sqlite3
```

Create env and activate it:

```bash
virtualenv --python=`which python3` django-test
cd django-test
source bin/activate

$ pip3 install wheel rope jedi Django
```

Create and start new project(you need to be inside the env):

```bash
$ django-admin startproject hreniuc_cristian_3712a

$ cd hreniuc_cristian_3712a
$ python3 manage.py migrate
$ python3 manage.py runserver
```

Now open the browser: http://localhost:8000/

Create new app:

```bash
$ python3 manage.py startapp lab4_cv
```

Create superuser:

```bash
$ python3 manage.py createsuperuser
```

After adding models:

```bash
$ python3 manage.py makemigrations lab4_cv
$ python3 manage.py migrate
$ python3 manage.py runserver
```