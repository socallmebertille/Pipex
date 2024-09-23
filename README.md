# Make a Pipex project

<br>

## blog : comprendre les fonctions pipe, fork et dup2

<br>

```
https://www.rozmichelle.com/pipes-forks-dups/
```

<br>

## fonctionnement du pipe

<br>

```
int fds[2];

pipe(fds);
```

<br>

Le pipe cree un canal entre 2 descripteurs de fichiers. Ce qui est ecrit dans fds[1] (ex: sortie de cmd1) peut etre lu par fds[0] (ex: entre de cmd2). Les 2 descripteurs sont connectes en interne, et le pipe stocke temporairement les donnees pour la communication entre processus.

<br>

## fonctionnement du fork

<br>

```
pid_t pid;  // pid_t = type pouvant contenir un id de processus

pid = fork();
```

<br>

Le fork cree un processus enfant (copie du processus parent) en dupliquant le processus parent (processus en cours).
<br>
Globalement, on l'utilise pour permettre l'execution de 2 commandes differentes (cmd1 et cmd2) simultanement dans differents processus et, ensuite pouvoir les faire communiquer via le pipe.

<br>

## fonctionnement de waitpid

<br>

```
pid_t pid1;
pid_t pid2;

pid1 = fork();
pid2 = fork();

...

waitpid(pid1, NULL, 0);
waitpid(pid2, NULL, 0);
```

<br>

Le waitpid permet au processus parent (=principal) d'attendre la fin des deux processus en cours ayant pour id pid1 et pid2.
<br>
Il peut etre nescessaire d'avoir recours a cette demarche par exmeple lorsque l'on a la ligne de code suivant :

<br>

```
time ./pipex infile 'sleep 9' 'sleep 5' /dev/stdout
```

<br>

Ici, on affiche dans la sortie standard le temps qu'a mis le programme a executer les cmd1 et cmd2. C'est-a-dire 9 secondes, grace au waitpid. Dans le cas ou waitpid n'aurait pas ete utilise, la sortie aurait ete de 5 secondes car c'est la derniere commande enregistree.

<br>

## fonctionnement du dup2

<br>

```
dup2(infile, STDIN_FILENO);
dup2(fds[1], STDOUT_FILENO);
close(infile);
close(fds[0]);
close(fds[1]);

dup2(outfile, STDOUT_FILENO);
dup2(fds[0], STDIN_FILENO);
close(outfile);
close(fds[0]);
close(fds[1]);
```

<br>

Par defaut, chaque programme a pour entre STDIN = 0 et pour sortie STDOUT = 1.
<br>
Or, dans ce cas, on souhaite lire le fichier d'entree, executer la premiere commande et la stocker dans le pipe. C'est ce que fait dup2, il redirige l'entre standard initialement 0 vers infile (= resultat de open(infile)) et la sortie initialement 1 vers la sortie du pipe (= fds[1]).
<br>
De meme pour la cmd2, on souhaite rediriger l'entre standard initialement 0 vers l'entre du pipe (= fds[0]) et la sortie initialement 1 vers outfile (= resultat de open(outfile)).
<br>
La fonction dup2(fd1, fd2) permet donc de faire une copie de fd1 vers fd2 et ferme fd1 s'il avait ete ouvert avec open auparavant. A noter que si l'appel a dup2 ne se deroule pas comme prevu, dup2 ne fermera pas fd1. Aussi, si les valeurs de fd1 et fd2 sont equivalentes, dup2 ne fera rien, et ne renverra aucun message d'erreur.

<br>

## fonctionnement de execve

<br>

```
execve(cmd_path, cmd, envp);
```

<br>

Cette fonction va nous permettre d'executer les commandes envoyes. Pour cela, il lui faut le path (= chemin d'acces la commande stocke au sein de l'ordinateur), la commande (= tableau de strings dont la commande puis son ou ses flags dans plusieurs strings differentes) et l'environnement.

<br>

### recuperer les commandes

<br>

L'idee est donc de recuperer chaque commande et ses potentiels flags. On va donc grossierement split les arguments qui correspondent aux commandes (soit av[2] et av[3]) avec des espaces.
<br>
On veut par exemple obtenir :
<br>
| tr  |
|-----|
| a-z |
| A-Z |

<br>

### a la recherche du path

<br>

```
int	main(int ac, char **av, char **envp)
```
<br>

Pour cela, on commence par recuperer un 3eme argument dans le main, qui correspond donc a l'environnement (= conserve la trace des informations partagées par de nombreux programmes, qui changent rarement et qui sont moins fréquemment utilisées).
<br>
Apres cela, on va aller cherche la string qui commence par "PATH=" et recuperer tout ce qui vient a la suite de cette string. C'est-a-dire qu'on se retrouve avec une suite de plusieurs chemins possibles separes avec ':'. On va donc split ces chemins.
<br>
Une fois cela fait, on va tester avec la fonction access chaque string de path potentiel suivi de '/' et de la commande que l'on veut executer (cmd1[0] ou cmd2[0]). On va ajouter les flags 'F_OK | X_OK' a la fonction access pour verifier l'existence et le droit d'execution de la commande en question.
<br>

On oublie pas la gestion d'erreur, de free et de close pour ibtenir un programme coherent et correct !

<br>