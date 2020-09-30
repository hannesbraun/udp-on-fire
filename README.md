# UDP on Fire

Have you ever wanted to see how unreliable UDP really is? This might be the tool for you. Maybe.

## How does it work?

Super simple: the sender is constantly sending increasing numbers via UDP (one integer per packet) starting from zero.
As soon as the receiver doesn't receive the number he expects (previous number + 1) a message will be printed to stdout.
The message is of the format `<expected number> : <received number>`.
Well, as you can see, there is no detailed analysis of the errors... but at least, it's fun to see how often unexpected things happen.

## Building from source

*A POSIX-compliant system is required to build and run this software.*

Compile both the server and the client with:
```sh
make
```

You will find the sender and receiver executable in the root directory of the project.

## Usage

Start the receiver with something like `./receiver`.
Now start a sender with something like `./sender <Receiver IP>` and watch the receiver's console.

## License

UDP on Fire is released under the GNU General Public License, version 3. For more information see [LICENSE](LICENSE "GNU General Public License, Version 3").

## Author

Hannes Braun (<hannesbraun@mail.de>)
