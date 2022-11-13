DROP SCHEMA campus;

CREATE DATABASE campus;

USE campus;

CREATE TABLE student (
    id INT AUTO_INCREMENT PRIMARY KEY,
    passwd VARCHAR(32) NOT NULL DEFAULT "0",
    name VARCHAR(32),
    sex CHAR(1) CHECK (sex = 'f' OR sex = 'm'),
    school VARCHAR(32),
    major VARCHAR(32)
);

CREATE TABLE card (
    id INT AUTO_INCREMENT PRIMARY KEY,
    student_id INT,
    balance INT DEFAULT 0 CHECK(balance >= 0),
    FOREIGN KEY(student_id) REFERENCES student(id) ON DELETE CASCADE
);

INSERT INTO student(id, passwd, name) VALUES (1, "qwer", "admin");