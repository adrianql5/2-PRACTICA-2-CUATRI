Insert into categoria values ('Bases de Datos', 'Libros con contenidos relacionados con la tecnolog�a de Sistemas Gestores de Bases de Datos');
Insert into categoria values ('Programaci�n', 'Libros relacionados con lenguajes y t�cnicas de programaci�n');


Insert into libro (titulo,isbn,editorial,paginas, ano) values ('Fundamentos de bases de datos', '84-481-3654-3', 'McGraw Hill', 787, '2002');
Insert into autor (nombre, orden) values ('A. Silberschatz', 1);
Insert into autor (nombre, orden) values ('H.F. Korth', 2);
Insert into autor (nombre, orden) values ('S. Sudarshan', 3);
Insert into cat_tiene_libro (categoria) values ('Bases de Datos');
Insert into ejemplar (ano_compra, localizador) 
	values('2004','prxd34');
Insert into ejemplar (ano_compra, localizador) 
	values('2005','prxd45');

Insert into libro (titulo,isbn,editorial,paginas, ano) values ('An introduction to database systems','0-321-18956-6', 'Pearson/Addison-Wesley', 983, '2003');
Insert into autor (nombre, orden) values ('C.J. Date', 1);
Insert into cat_tiene_libro (categoria) values ('Bases de Datos');
Insert into ejemplar (ano_compra, localizador) 
	values('2004','dsadt3');
Insert into ejemplar (ano_compra, localizador) 
	values( '2008','dsadt56');

Insert into libro (titulo,isbn,editorial,paginas, ano) values ('Programaci�n en Java','1-235-25345-6', 'Springer', 300, '2005');
Insert into autor (nombre, orden) values ('A.P. Sanchez', 1);
Insert into autor (nombre, orden) values ('N. Theodoridou', 2);
Insert into cat_tiene_libro (categoria) values ('Programaci�n');
Insert into ejemplar (ano_compra, localizador) 
	values('2010','fgf5457');

Insert into libro (titulo,isbn,editorial,paginas, ano) values ('Desarrollo de aplicaciones con PHP y PostgreSQL','0-123-12345-6', 'Idea Group Inc.', 120,  '2004');
Insert into autor (nombre, orden) values ('N. Theodoridou', 1);
Insert into cat_tiene_libro (categoria) values ('Bases de Datos');
Insert into cat_tiene_libro (categoria) values ('Programaci�n');
Insert into ejemplar (ano_compra, localizador) 
	values( '2005','dsa3g65');
Insert into ejemplar( ano_compra, localizador) 
	values('2011','dsa3g89');	


insert into usuario values ('JAlvarez','pja','Juan Alvarez', 'C Blanco Amor', 'JAlvarez@bibdb.es', 'Administrador');
insert into usuario values ('ERomero','per','Elisa Romero', 'C Rosalia de Castro', 'ERomero@comp1.com', 'Normal');
insert into usuario values ('FPerez','pfp','Francisco Perez', 'C del olvido', 'novotom@locamost.org', 'Normal');
insert into usuario values ('SSuarez','pss','Sara Suarez', 'C de la rosa', 'ss34@alo.com', 'Normal');


insert into prestamo (usuario, libro, num_ejemplar, fecha_prestamo, fecha_devolucion)
values ('ERomero', 2, 1, '2025-02-15', '2025-03-15');

insert into prestamo (usuario, libro, num_ejemplar, fecha_prestamo, fecha_devolucion)
values ('FPerez', 1, 2, '2025-02-25', NULL);

insert into prestamo (usuario, libro, num_ejemplar, fecha_prestamo, fecha_devolucion)
values ('SSuarez', 1, 1, '2025-03-10', NULL);


