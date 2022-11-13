# Campus Card System

## Introduction

This toy project is continuously evoling. I'will continuously experiment new tech I learn with it, and this project will be treated as seriously as I could to make it readable.

## Building Guides

- GNU Make 4.3
- clang 14.0.0
- libmysqlcppconn-dev 8.0+ (installed globally)
- mysql 8.0+

```sh
# first start mysql sever at localhost
sudo systemctl start mysql
# build project
cd your-directory-location
make clean
make
# initialize the database
make reset_database
# run the executable
./build/bin/campus_card_system
```

## Usage

### For Administrator

As the only administrator, you're provided with an super admin account(id=`1`, passwd=`qwer`).

### For Students

Your id is allocated by administrator, and the passwd defaults to be `0`.
