# Synthez

#### Format du fichier de configuration

Les fichier de configuration sont au format ``xml``

Les fichiers sont décomposés de tel sorte :

- Un entête xml classique

```xml
<?xml version="1.0" encoding="UTF-8" ?>
```

- Une rubrique ``music`` dans laquelle on précise le tempo et la durée

```xml
<music tempo="180" duration="30">
...
</music>
```

- Vient ensuite la rubrique ``track`` qui contient les infomations sur une piste et le fichier de son à utliser

***Note: Il est possible de créer autant de piste que voulu***

```xml
<track id="0" name="Track" type="M">
  <soundfile src="./guitar"></soundfile>
  ...
</track>
```

- Il faut ensuite préciser pour chaque temps quelles notes seront jouées

Les notes vont de 0 à 11, correspondant au tableau suivant :

 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 
---|---|---|---|---|---|---|---|---|---|----|---
La |La#|Si |Do |Do#|Re |Re#|Mi |Fa |Fa#|Sol |Sol#
```xml
<time id="0" notes="0,4,5"></time>
<time id="1" notes="0,8,15"></time>
<time id="2" notes="3,6,8"></time>
<time id="3" notes="1,7,9"></time>
<time id="4" notes="3,8,12"></time>
<time id="5" notes="0,1,2,3"></time>
<time id="6" notes="4,6,12"></time>
<time id="7" notes="1,2,3"></time>
...
```
