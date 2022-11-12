# Campus Card System

Campus card system provide a unified interface for administrators and users.

Students can use it to consume, check their balance, declare the lost of their campus card and show their identities. Managers can check and update student's information easily with this system.

## Introduction

### For Administrator

You're provided with an super admin account(id=`000`, passwd=`628`), which could manage all managers.

- Only super administrator could manage administrator's account. You should only use it when you need to CRUD admins' accounts.
- All administrator could manage any student's account.
- Student's card will be deleted if the student is removed from the system.
- Student's old card will be deleted if you bind new card to her/him.

### For Students

- The initial passwd is `0`
- `Activate`: Change the passwd to activate it. (passwd should be shorter than 6 digits)
- `Lost`: Set your card as `lost` would make the card unable to recharge and pay.

