-- Copyright (c) 2025 Adrián Quiroga Linares Lectura y referencia permitidas; reutilización y plagio prohibidos

drop table usuario;
drop trigger beforeInsertEjemplares ON ejemplar;
drop function introduce_num_ejemplar();
drop table ejemplar;
drop table cat_tiene_libro;
drop table autor;
delete from libro;
drop trigger afterLibros ON libro;
drop function controla_secuencias_libro();
drop table libro;
drop sequence seq_libro_id_libro;
drop table categoria;
drop table prestamo;
