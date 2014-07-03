Linux Diagnostics Center
================================================================

The Linux Diagnostic Center (LDC) is a software tool that allows
easy access to hardware information of computers and servers.

Along with the tool, the LDC also provides the libldc, a C library
allows the developer to obtain hardware information from third
part projects.


Dependencies
================================================================

LDC can run despite the existence of all dependences, plugins are
executed individually. The absence of a dependency affects only
the plugin that uses that dependency.

This is designed to work with:
- dmidecode
- libparted
- libc


Install
================================================================

To install, use::

  sudo make build install


Important References
================================================================

List of contributors of the project.

- Adriano Melo <astm@cin.ufpe.br>
- Hugo Alencar <hraa@cin.ufpe.br>
- Dayvid Victor <dvro@cin.ufpe.br>
- Thyago Porpino <tnp@cin.ufpe.br>
