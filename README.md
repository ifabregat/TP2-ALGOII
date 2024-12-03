<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TP 2

## Repositorio de Ivan Emanuel Fabreagt - 112287 - ifabregat@fi.uba.ar

- Para compilar:

Opcion1:
```bash
gcc -Wall -Werror -O2 -g -c extra/engine.c -o engine.o && \
gcc -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g src/*.c tp2.c engine.o -o tp2
```

Opcion2:
```make
make tp2
```

- Para ejecutar:

```bash
./tp2 datos/pokedex.csv
```

- Para ejecutar con valgrind:
```bash
valgrind --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes ./tp2 datos/pokedex.csv
```

- Para ejecutar pruebas* y luego tp2
```make
make
```
```text
* hay dos pruebas que estan comentadas, ya que el bot tiraba time out. Fueron hechas para probar que el menu funcionara de forma adecuada.
```

---
#  TDAs creados

## Menu

### Estructuras

* **menuItem**: contiene un `char` para la opcion, contiene una `char *` y contiene un puntero a funcion tipo `bool` que recibe como parametro dos `void *`.

* **menu**: contiene un puntero a un tipo de dato tipo `lista`.

<div align="center">
<img height="200" width="49%" src="img/menuItem_t.jpg">
<img height="200" width="49%" src="img/menu_t.jpg">
</div>

### Funciones
* **menu_crear**: reserva memoria para la variable de tipo `menu`. Despues al campo `opciones` le asigna la `lista` devuelve de la funcion `lista_crear`.

* **menu_destruir**: recibe un puntero al `menu_t` para el menu y un puntero a la funcion `destructor` para aplicarle a cada elemento. Libera la lista del campo opciones utilizando la funcion `lista_destruir_todo` con el destructor pasado por parametro. Despues libera la memoria utilizada para el `menu`.

* **menu_agregar_opcion**: recibe un puntero al `menu_t` para el menu, un `char` para el caracter, un `char *` para la descripcion y un puntero a la `funcion` de tipo bool. Transforma el caracter a mayuscula y lo busca en la `lista` de opciones. Si esta devuelve `false`, caso contrario reserva memoria para un `menuItem` y asigna los valores y devuelve `true`.

* **menu_mostrar**: recibe un puntero al `menu_t` para el menu. Con un for itera hasta el valor retornado por `lista_cantidad_elementos`. En cada iteracion obtiene el elemento `menuItem` de la lista con `lista_obtener_elemento` a traves del indice y lo muestra con determinado formato. Al final aparece un mensaje para que ingrese la opcion (la parte de como pide queda a disposicion del usuario).

* **menu_ejecutar_opcion**: recibe un puntero al `menu_t` para el menu, un `char` para el caracter y dos `void *` por si necesitara usarlos. Transforma el caracter a mayuscula y lo busca con la funcion `lista_buscar_elemento`. Si el item no esta devuelve `false`, caso contrario realiza la accion asociada pasandole el `void *` como parametro.

## Pokedex

### Estructuras

* **pokemon**: contiene un `char *` para el nombre, un `int` para el puntaje, un `char *` para el color y un `char *` para el movimiento.

<img align="right" height="300" width="500px" src="img/pokemon_t.jpg">

### Funciones

* **pokedex_crear**: creo un puntero a `lista` y le asigno la lista que devuelve la funcion `lista_crear`.

* **pokedex_destruir_todo**: recibe un puntero a la `lista` y un puntero a la funcion `destructor`. Llama a la funcion `lista_destruir_todo` con el destructor pasado como parametro.

* **pokedex_agregar_pokemon**: recibe un puntero a `lista` con la lista de pokemones y un `char *` para la ruta del archivo. Llama a la funcion `abrir_archivo_csv` y pasa la `ruta` del archivo y el separador `,`. Asigno los parseadores a la `funcion parseadores`, generalizo la memoria a pedir que sea de **100 bytes** para los strings y vinculo las variables donde se guardaran esos datos en `ctx`. Con un ciclo while leo cada linea con la funcion `leer_linea_csv`. Convierto el color a su `codigo ansi` para asi poder crear el pokemon con la funcion `pokemon_crear`. Una vez que lo crea, lo agrego al final de la lista. Libero la memoria que pedi para los strings y cierro el archivo con la funcion `cerrar_archivo_csv`. Si todo salio bien devuelve `true`, caso contrario `false`.

* **pokedex_ordenar**: recibe un puntero a `lista` con la lista de pokemones y un puntero a la funcion `comparador` para obtener el criterio de orden. Con el metodo de burbujeo ordena los elementos de la lista utilizando un `void *` temporal para quitar y agregar los elementos en la lista.

* **pokedex_cantidad**: recibe un puntero a `lista` con la lista de pokemones. Llama a la funcion `lista_cantidad_elementos` y retorna su valor.

* **pokedex_obtener_pokemon**: recibe un puntero a `lista` con la lista de pokemones y un `size_t` para la posicion en la lista a acceder. Llama a la funcion `lista_obtener_elemento` y retorna ese dato tipo `pokemon` o `NULL` si no lo encontro.

* **pokedex_obtener_pokemon_random**: recibe un puntero a `lista` con la lista de pokemones. Obtiene la cantidad de elementos de la lista con la funcion `lista_cantidad_elementos` para utilizar la funcion `rand` y limitar los valores. Llama a la funcion `lista_obtener_elemento` y retorna ese dato tipo `pokemon` o `NULL` si no lo encontro.

* **pokedex_iterar_pokemones**: recibe un puntero a `lista` con la lista de los pokemones, un puntero a la funcion `funcion` tipo bool que recibe un `pokemon_t` y un `void *` para usar con el **iterador externo** y por ultimo un `void *` como ctx por si lo necesita. Llama a la funcion de `ordenar_pokedex` y luego retorna el valor de llamar `lista_iterar_elementos`.

## Juego

### Estructuras

* **pokemonTablero**: contiene un `int` para la posicion x, un `int` para la posicion y, un `char *` para el nombre, un `char` para la primer letra, un `int` para el puntaje, un `char *` para el color, un `char *` para el movimiento y un `size_t` para llevar en que caracter del string moviemiento esta.


* **jugador**: contiene un `int` para la posicion x, un `int` para la posicion y, un `int` para el puntaje, un `int` para el multiplicador, un `int` para los movimientos, un `int` para los pokemones atrapados, un `pokemonTablero_t *` para el ultimo pokemon atrapado, un `Pila *` para la pila de pokemones en la racha actual y un `Pila *` para la pila de pokemones en la mayor racha.

* **tablero**: contienen un `int` para el ancho, un `int` para el alto, un `char **` para las celdas, un `Lista *` para los pokemones y un `Lista *` para los pokemones atrapados.

<div  align="center">
<img  height="400" width="339px" src="img/pokemonTablero_t.jpg">
<img  height="400" width="300px" src="img/jugador_t.jpg">
<img  height="400" width="420px" src="img/juego_t.jpg">
</div>

* **juego**: contiene un `jugador_t *` para el jugador, un `tablero_t *` para el tablero, un `Lista *` para la pokedex, un `int` para las iteraciones, un `int` para la semilla y `bool` para validar si se termino el juego.

<div  align="center">
<img  width="90%" src="img/tablero_t.jpg">
</div>

### Funciones

* **destructor_pokemones_tablero**: recibe un `void *`. Se encarga de liberar la memoria pedida para los datos tipo `pokemonTablero`.

* **tablero_crear**: recibe un puntero a `Lista`. Asigna el alto y ancho a los valores 15 y 32. Reserva memoria para un **char** para cada celda de la matriz (por eso **char ****) y los inicializa con un espacio en blanco con `memset`. Asigna la lista pasada por parametro a lista de los pokemones y crea una lista para los atrapados.

* **tablero_destruir**: recibe un puntero a `tablero_t` y un puntero a la funcion `destructor`. Se encarga de liberar la memoria pedida para cada celda y utiliza la funcion de `lista_destruir_todo` para destruir las listas con el `destructor` pasado.

* **encontrar_pokemon_en_posicion**: recibe un puntero a `Lista` con la lista de los 7 pokemones para el tablero, un `int` con la posicion x y un `int` con la posicion y. Con el **iterador interno** recorre la lista y verifica si el pokemon en esa posicion de la lista coincide con las posiciones pasadas. Si coincide retorna ese dato tipo `pokemonTablero_t`, caso contrario `NULL`.

* **tablero_imprimir**: recibe un puntero a `juego_t` con el juego. Muestra unos datos de interes para el usuario y a continuacion imprime el tablero. Si la posicion de ambos ciclos for coincide con la del jugador o la del pokemon a llamar la funcion de **encontrar_pokemon_en_posicion** imprime el caracter.

* **tablero_eliminar_pokemon**: recibe un puntero a `Lista` con los pokemones, un puntero a `Lista` para los pokemones atrapados y un puntero a `pokemonTablero_t` para el pokemon. Con el **iterador interno** recorre la lista para ver si se encuentra el pokemon pasado, si coincide lo quita y lo agrega al final de la lista de atrapados. Devuelve el `pokemon atrapado` si es que la funcion de `lista_quitar_elemento` lo encontro, caso contrario `NULL`.

* **tablero_agregar_pokemon**: recibe un puntero a `Lista` con la pokedex y un puntero a `Lista` con los pokemones del tablero. Obtiene la cantidad de elementos de la pokedex para asi poder usar la funcion `rand` y que devuelva un numero entre ese rango. Con ese indice averiguo la posicion random de un pokemon de la pokedex, me copio los valores en otras variables las cuales les reservo memoria y agrego al pokemon a lista de los pokemones del tablero.

* **jugador_crear**: reservo memoria para la estructura y asigno los valores iniciales a los campos. Para las rachas uso el tipo de dato `Pila`, permitiendome acceder rapidamente al ultimo ingresado.

* **jugador_destruir**: recibe un puntero a `jugador_t` y un puntero a una funcion `destructor`. Libera la memoria de las **pilas**. Primero verifico si estan vacias, si no lo estan le aplico a cada elemento la funcion `destructor`, caso contrario solo libero la estructura.

* **max**: recibe un int para el primer elemento y un int para el segundo elemento. Devuelve el mayor de los elementos.
* **min**: recibe un int para el primer elemento y un int para el segundo elemento. Devuelve el menor de los elementos.

* **procesar_movimiento_pokemones**: recibe un puntero a `Lista` con la lista de los pokemones del tablero y un `int` con la conversion a ascii de la tecla presionada. A traves del iterador interno recorre la lista de los pokemones del tablero. Aplicandole a cada uno la correccion de los campos posicion x y posicion y dependiendo del campo indice de movimiento que lleva la cuenta sobre el patron de movimiento.

* **procesar_entrada**: recibe un `int` con la conversion a ascii de la tecla presionada, un puntero a `jugador_t` con el jugador y un puntero a `Lista` con la lista de pokemones del tablero. Realiza la correcion de los campos x e y del jugador segun la tecla presionada y llama a la funcion `procesar_movimiento_pokemones`. Utiliza las funciones de `max` y `min` para que no se salga del tablero.

* **administrar_puntaje**: recibe un puntero a `jugador_t` con el jugador y un puntero a `pokemon_tablero_t` con el pokemon atrapado. Si es el primer pokemon atrapado lo agrega a la **pila** de `racha actual`. Despues realiza una comparacion con el ultimo elemento de la `racha actual` con el pokemon atrapado si coinciden letra o color se agrega a la `racha actual`. Caso contrario realiza una comparacion para ver si la `racha actual` tiene mayor cantidad de elementos que la `racha mayor` y acomoda las pilas de rachas. Al final calcula el puntaje.

* **logica**: recibe un `int` con la conversion a ascii de la tecla presionada y un puntero a `void` para los datos. Esta funcion tiene la logica del juego. Verifica si se encuentra un pokemon en la misma posicion del jugador y si es asi lo guarda en atrapado. Aca llama a la funcion `atrapar_pokemon` que recibe un puntero a `juego_t` y un puntero a `pokemonTablero_t` que llamara a las funciones de **administrar_puntaje**, **tablero_eliminar_pokemon** y **tablero_agregar_pokemon**. Tambien verifica que el temporizador no haya llego a 60 ni que la entrada sea 'q' o 'Q' para salir, si esto pasa asigna terminado en `true`. Al final de cada ciclo retorna esta variable ya que si es true (1) termina la funcion `game_loop`.


# TP2

Se utilizan todos los archivos y en consecuencia sus funciones. Se inicializa el menu con las opciones, descripciones y acciones ya definidas. Utilizo dos variables de tipo bool que son interfaz y continuar. El menu se va a mostrar mientras que interfaz sea `true` y cuando se pide el ingreso de la opcion se pasa a la funcion `menu_ejecutar_opcion` la direccion de memoria de continuar. Esta se actualiza a `true` o `false` si esta termina en false significa que interfaz debe ser false y termina el ciclo del menu.

* **mostrar_pokedex**: recibe dos puntero a `void`con un flag si debe seguir en el menu y con la ruta del archivo. Crea una pokedex con la ruta ya establecida en el codigo y la itera en orden mostrando cada uno con un formato decente. Y asigna a contexto como `true`, ya que se desea volver a mostrar el menu.

* **juego**: recibe un `int` para la semilla y un puntero a `void` con la ruta del archivo. Realiza las creaciones de lista y carga de estas como asi de algunos valores importantes a la hora de comenzar el juego.

* **sin_semilla**: recibe dos punteros a `void` con un flag si debe seguir en el menu y con la ruta del archivo. Inicializa la semilla random con time, srand, rand y de nuevo srand. Y llama a juego con esa semilla . Esta funcion contiene la inicializacion de las estructuras y comienzo del juego. Y asigna a contexto como `false`, ya que se desea terminar de mostrar el menu.

* **con_semilla**: recibe dos punteros a `void` con un flag si debe seguir en el menu y con la ruta del archivo. Pregunta por la semilla y llama a juego pasandole esa semilla. Esta funcion contiene la inicializacion de las estructuras y comienzo del juego. Y asigna a contexto como `false`, ya que se desea terminar de mostrar el menu.

* **salir**: recibe dos punteros a `void` con un flag si debe seguir en el menu y con la ruta del archivo . Y asigna a contexto como `false`, ya que se desea terminar de mostrar el menu.

<div  align="center">
<img  width="90%" src="img/memoria.jpg">
</div>


# TDAs reutilizados

Principalmente fueron reutilizados los TDAs `Lista` y `Pila`. A su vez tambien use los archivos que fueron desarrollados al principio de la materias `split` y `csv`.

El TDA-Menu se encarga de crear un menu el cual tiene una opcion, descripcion y una accion asociada. En su inicio habia pensado usar el TDA-Hash para la implementacion, pero lo descarte ya que no tenia certeza que al aplicarle la funcion de hash a la descripcion me quedaran en orden. Por lo que me tire a implementarlo con el TDA-Lista. Ademas hay que entender que para este caso el menu tendria solo 4 opciones primordiales, por lo que no serian costosas las operaciones.

El TDA-Pokedex fue una fusion de operaciones que se realizaron entre el `tp1` y el `tp_lista`. Por eso decidi que fuera un TDA. Las operaciones principales son las leer de un archivo los datos y agregarlos a una lista. A su vez tambien esta la idea de obtener un pokemon random como uno en especifico o la de iterar los pokemones. en el medio me surgio de hacerlo con el TDA-Hash, pero paso algo similar a lo que me paso con el TDA-Menu. Ya que al agregar pokemones al aplicarle la funcion de Hash al nombre  no me garantizaba que fueran a distintos indices, por lo que me podria haber quedado una lista de nodos enlazados (era lo mismo que hacer una lista). Mas al final me surgio la posibilidad de hacerlo con el TDA-ABB pero no termine de visualizar como seria.

Para no implementar toda la logica del juego en el archivo del `tp2` decidi hacerlo en otro archivo. En este sente las estructuras que necesitaria para almacenar los datos necesarios durante el juego. Crea algunas estructuras pidiendo memoria y despues la libera, procesa la entrada y por siguiente los movimientos y el puntaje. En este "TDA" fue que implemente el TDA-Pila para el uso de racha y optimizar las operaciones. A la hora de atrapar se guarda en la racha actual si se atrapa uno que aumenta la racha se sigue agregando a esa pila si se corta la racha se compara con la racha mas larga (inicialmente vacia) y hace desapilamientos de `rachaActual` a apilamientos a `rachaMayor`. Ya que a lahora de mostrar la racha mas larga va a ser solo desapilar el ultimo elemento y lo voy mostrando. Todo es optimiza la operaciones ya que el TDA-Lista esta implementado con un puntero al primer nodo como al ultimo nodo.

*Ambos TDAs usados fueron modificados para bien, despues de la pre-entrega, pre-re-entrega o post-entrega y post-re-entrega* 

# Comentario extra

En el secundario empezamos viendo diagramas de flujos, luego pseudocodigo y por ultimo python cosas muy basicas. Y desde ese momento se me hacia muy dificil visualizar un juego hecho en python ya que pensaba "como logro toda la interfaz esa, no se puede" (por el hecho de una interfaz grafica de un juego de hoy en dia). 

Y me meti en la carrera por las computadoras y la matematica. Al momento de la inscripcion al CBC justo hicieron el cambio por lo que tuve pensamiento computacional. Lo que odie el uso de las funciones porque no terminaba de entender el uso del `return` por lo nunca me gustaba modularizar ya que no lo terminaba de entener. Al final la promocione. 

Ya en la "carrera" cursando Fundamentos de programacion vimos lo basico y no tuvimos que hacer ninguna entrega de nada practicamente. Por lo que me quedo un mal gusto del lenguaje, en ese momento pensaba que para que veiamos un lenguaje "viejo" y que hoy en dia hay otros nuevos que sirven para las cosas hoy. Para colmo, tambien la aprobe. 

Y aca estoy, decidi meterme en esta catedra sabiendo que tenia bastantes entregas de tps (lo que no sabia era que eran uno atras del otro) por lo que necesite adaptarme al ritmo rapido. Y me adapte, con el primero que tuve problema fue con el `tp1` por el uso de la memoria. La profesora me comento unas cosas y las intente implementar y despues de eso pude entender mucho mejor el uso de los `mallocs`, `reallocs` y `frees`. Para el de ABB fui canchero  con el uso de la memoria, pero no con la recursion (si de por si odio las funciones tener que llamarla desde dentro era peor todavia). Y con  TDA de hash me costo ver a que hacia referencia el concepto de *tabla*, pero sacando eso de lado pude. 

Y llegue al ultimo, al principio costo la idea de implementar el menu, pero pude. Despues segui con el de pokedex que fue paracido al `tp1` y `tp_lista` con eso fue lo unico que tuve problemas. La clase que vimos un poco como empezar a implementar el tp fue de muchisima ayuda. Y pude empezar a encararlo, pero hubieron inconvenientes. Cuando lograba implementar que se movieran y comieran y aparecieran mas en algun punto o rompia o habia perdida de memoria o intentaba a acceder a memoria que ya fue liberada. Por ese motivo lo borre y arraque 3 veces el tp. Por eso me dije "vamos a calmarnos y lo empezamos junto a las pruebas" y asi salio. Si es cierto que hay algunas partes que no son tan claras o las mejores opciones pero fue tanta la frustracion que si lograba cumplir algo me hacia un *git add* y *git commit* a mi repositorio para guardar el progreso y saber desde cuando empezo a romper. 

En este momento puedo decir que funciona que el juego se puede jugar(lo probaron hermanas, amigos/as y pareja y la primita de ella).

Finalmente puedo decir, que me gusta el lenguaje C, perdi todos los miedos y le agarre la mano.
