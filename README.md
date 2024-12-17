# FdF : Wireframe Map Visualizer 🗺️

**FdF** est un projet graphique permettant de visualiser des cartes en fil de fer (wireframes) en 3D à partir de fichiers `.fdf`. Ce projet utilise la **MiniLibX** pour créer un rendu interactif dans une fenêtre graphique.

---

## 🖼 Aperçu Visuel

![Aperçu de FdF](https://user-images.githubusercontent.com/xxxxxxx/placeholder-image.png)

---

## 🚀 Prérequis

Pour compiler et exécuter ce projet, vous aurez besoin de :
- **Linux** (requis pour MiniLibX)
- **GCC** et **Make**
- **MiniLibX** (incluse dans le projet)
- **Libft** (incluse dans le projet)

---

## 🛠️ Installation

1. **Clonez le projet** :
   ```bash
   git clone https://github.com/ufalzone/FdF.git
   cd FdF
   ```

2. **Compilez l'exécutable** :
   ```bash
   make
   ```

3. **Lancez avec un fichier de carte** :
   ```bash
   ./fdf maps/42.fdf
   ```

---

## 💟 Utilisation

### Controles clavier:

#### **Déplacements:**
- ← ou A (**65361/97**)  : Déplacement vers la gauche
- → ou D (**65363/100**) : Déplacement vers la droite
- ↑ ou W (**65362/119**) : Déplacement vers le haut
- ↓ ou S (**65364/115**) : Déplacement vers le bas

#### **Zoom:**
- `+` (**61**) : Zoom avant
- `-` (**45**) : Zoom arrière

#### **Hauteur (axe Z):**
- P (**112**)      : Augmente la hauteur
- O / Q (**111/113**) : Diminue la hauteur

#### **Rotation:**
- X (**120**) : Rotation autour de l'axe X
- Y (**121**) : Rotation autour de l'axe Y
- Z (**122**) : Rotation autour de l'axe Z

#### **Projection:**
- 1 (**49**) : Vue parallèle (angle_iso = 0)
- 2 (**50**) : Vue isométrique (angle_iso = 30)

#### **Contrôles:**
- R (**114**)     : Réinitialise tous les paramètres
- ESC (**65307**) : Ferme la fenêtre

---

## 📂 Format des fichiers `.fdf`

Les fichiers `.fdf` représentent des cartes sous forme de grille. Chaque chiffre correspond à une hauteur.

Exemple :
```
0  0  0  0  0
0  1  1  1  0
0  1  2  1  0
0  1  1  1  0
0  0  0  0  0
```

---

## 🛠️ Structure du Projet

```
FdF/
├── includes/        # Fichiers d'en-tête (.h)
├── libft/           # Bibliothèque libft
├── minilibx-linux/  # Bibliothèque graphique MiniLibX
├── srcs/            # Fichiers sources (.c)
├── maps/            # Exemples de fichiers .fdf
├── Makefile         # Script de compilation
└── README.md        # Documentation du projet
```

---

## 💿 Détails sur le Projet

Le projet **FdF** a été développé dans le cadre du cursus de l'école **42**. Il permet d'afficher des cartes de terrain en 3D avec des interactions utilisateur fluides et optimisées.

- **Graphismes interactifs** grâce à la MiniLibX.
- **Manipulations en temps réel** : déplacement, zoom, rotation, et modification de la hauteur.
- **Support complet des projections parallèles et isométriques.**

### 🌟 Note obtenue : **125/100**

Ce score récompense l'attention portée aux détails, à la performance et à la qualité du code.

---

## 📚 Crédits

Développé par **[Ton Nom]** dans le cadre du projet **FdF** de l'école **42**.

---

## 📃 Licence

Ce projet est sous la licence **MIT**. Consultez le fichier [LICENSE](LICENSE) pour plus de détails.
