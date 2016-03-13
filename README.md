# Happy Coding





##  A Brief Step-to-step Tutorial

- First
    [Grasp the basic concepts of Github in 5 minutes](https://guides.github.com/introduction/flow/)

- Second
    [Download Github Desktop for windows](https://desktop.github.com/) and install it, and follows its brief tutorial.

- Third
    To get acquaint with Github, you can `fork` a repository from any place, and have fun with it.

- Fourth (**Important**)
    Clone the [LittleGengshen/LFS2016](https://github.com/LittleGengshen/LFS2016/) repository to your local PC (*Using Github Desktop*). 
    You should choose a local directory (named `A`) to place it. 
    There are just some .cpp or .h files in the repository.
    **Please** create a VisualStudio project at annother local directory and add the **source code files** in the directory `A` to the project.
    Have Fun!

- Other References
    Maybe you want to learn more about Github.
    [This is a guide for Github Desktop](https://guides.github.com/introduction/getting-your-project-on-github/)
    [There are many other guides](https://guides.github.com/)

##There is some general ideas to use this distributed version controller   **Github**


- Now we have 2 parallel branches, named `master` and `develop`. As its name reveals, `master` is the main branch, which is updated only to have a better AI (**Without a bug**)

    - `develop` is exactly the branch we can develop on. 

    - Everytime we want to **modify something**, or just do some debuging, **Create** a new branch from `develop`, then do the things you want on the new branch **Which is on your own PC**.(You needn't publish the new branch to online github repository) 

    - Once you finish(**After you test the new AI**), and you think it is better than the previous one, Make a `Pull Request` from this new branch to `develop`, and we can have a discussion about it, then commit the merge.(to allow the changes also emerge in branch `develop`)

    - Once the `Pull Request` is committed, then you can delete your own branch(the one you create just now).



