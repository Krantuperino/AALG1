#-----------------------
# IMPORTANTE: Los valores de los parametros de los ejercicio?_test deben ajustarse.
# Se asume que los ficheros fuente se llaman ejercicio1.c, ejercicio2.c,...,ordenar.h
#-----------------------

CC = gcc -ansi -pedantic -std=gnu99
CFLAGS = -Wall -g
EXESORT = ejercicio1 ejercicio2 ejercicio3 ejercicio4 ejercicio5 ejercicio6 
EXESEARCH = ejercicio1busq ejercicio2busq

all : $(EXESORT) $(EXESEARCH)
allsort : $(EXESORT)
allsearch : $(EXESEARCH)

.PHONY : clean
clean :
	rm -f *.o core $(EXESORT) $(EXESEARCH) test ejercicio5.log busqueda.dat

$(EXESORT) : % : %.o ordenacion.o tiempos.o permutaciones.o busqueda.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -o $@ $@.o ordenacion.o tiempos.o permutaciones.o busqueda.o

$(EXESEARCH) : % : %.o busqueda.o tiempos.o permutaciones.o ordenacion.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -o $@ $@.o busqueda.o tiempos.o permutaciones.o ordenacion.o

permutaciones.o : permutaciones.c permutaciones.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

 ordenacion.o : ordenacion.c ordenacion.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<
 
 busqueda.o : busqueda.c busqueda.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<


 tiempos.o : tiempos.c tiempos.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) $(CFLAGS) -c $<

ejercicio1_test:
	@echo Ejecutando ejercicio1
	@./ejercicio1 -limInf 1 -limSup 5 -numN 10

ejercicio2_test:
	@echo Ejecutando ejercicio2
	@./ejercicio2 -tamanio 1 -numP 5

ejercicio3_test:
	@echo Ejecutando ejercicio3
	@./ejercicio3 -tamanio 1 -numP 5

ejercicio4_test:
	@echo Ejecutando ejercicio4
	@./ejercicio4 -tamanio 1

ejercicio5_test:
	@echo Ejecutando ejercicio5
	@./ejercicio5 -num_min 1 -num_max 5 -incr 1 -numP 5 -fichSalida ejercicio5.log

ejercicio6_test:
	@echo Ejecutando ejercicio4
	@./ejercicio6 -tamanio 1

ejercicio1busq_test:
	@echo Ejecutando ejercicio1
	@./ejercicio1busq -tamanio 10 -clave 5

ejercicio2busq_test:
	@echo Ejecutando ejercicio2
	@./ejercicio2busq -num_min 10 -num_max 100 -incr 10 -n_veces 1 -fichSalida busqueda.dat


alltest: ejercicio1_test ejercicio2_test ejercicio3_test ejercicio4_test ejercicio5_test ejercicio6_test ejercicio1busq_test ejercicio2busq_test