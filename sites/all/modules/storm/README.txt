/* $Id: README.txt,v 1.1.2.4 2009/06/24 21:07:35 magnity Exp $ */

Documentation for STORM project management application.
- Project homepage: http://drupal.org/project/storm
- Issue tracking: http://drupal.org/project/issues/storm

--

Storm consists of a set of modules as follows: Storm (base module), Attributes (settings), Organizations, Projects, Tasks, Tickets, Timetrackings, People, Notes, Knowledgebase, Invoices and Expenses.

Each of these provides permissions to control the sharing of data with other users and organizations.
NB: This may conflict with other node access modules.

All components (except Attributes) are nodes, so can be extended as follows:

    * CCK can be used to add more fields to the Storm content types
    * Views can build customised views
    * Taxonomy can be used to tag the contents of the Storm nodes
    * Upload can be used to attach files to Storm nodes
    * Comments can be used to permit comments on each of the Storm nodes

Storm content nodes also all link together - for example, an invoice can be associated with an organization and project.

SEE BELOW FOR DETAILS OF EACH OF THE MODULES INCLUDED WITHIN THE STORM PACKAGE.


--Storm (base module)--
This module is required for all Storm installations provides a Storm dashboard which gives quick links for the other Storm modules as well as to the Storm administration section.

--Storm Knowledgebase--
Relying only on the Storm base module, this module provides a content type that can be used to collect together important pieces of knowledge, tips and tricks, and can also categorise them by topic.

--Storm Attribute--
Attributes are the values that are used within Storm, such as task status, countries, currencies etc. This module only relies on the Storm base module, but is needed by all of the following modules.

--Storm Organization--
This module allows you to create nodes relating to the organizations that are the stakeholders of your projects. If you wish to create invoices using Storm, your own organization should be created as an organization here.

--Storm People--
Storm People allows the creation of individual contacts within Organizations, and linking of these to Drupal user accounts.

--Storm Teammember--
This module allows the building of team working on a specific project / task / ticket.

--Storm Project--
Storm project allows creation of projects attached to organizations.

--Storm Task--
Storm tasks are the parts that compose a project and can be hierarchically nested to build a work breakdown structure.

--Storm Ticket--
Storm tickets can be used to track bugs, feature requests, or any other category as specified via attributes. They can be associated with an organization, project or task.

--Storm Timetracking--
This module allows the recording of time spent relating to particular organizations, projects, tasks or tickets.

--Storm Note--
This module allows notes to be attached to organizations, projects or tasks.

--Storm Invoice--
Within Storm Invoice, you can create invoices between yourself and clients. A printer friendly version comes included, and with the addition of the tcpdf library (see the INSTALL.txt), you can also download pdf versions of your invoices directly from Storm.

--Storm Expense--
Storm Expense allows the recording of expenses attached to a specific task or project, including information such as whether it is billable.