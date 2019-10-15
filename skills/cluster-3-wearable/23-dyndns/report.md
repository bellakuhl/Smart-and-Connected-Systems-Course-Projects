#  Dynamic DNS

Author: Isabella Kuhl, 2019-10-10

## Summary
In this skill we set up a DNS so that we are able to change the location of the router and still access it. We used the Raspberry Pi as a server and used port forwarding to forward requests to port 80 to the Pi which hosted the .js file to listen and display text on port 80. We used a Namecheap domain that a team member had already purchased for the DDNS which updated the IP address of the router.

## Sketches and Photos

Here is an image of the DNS setup:

![DNS](https://github.com/BU-EC444/Kuhl-Isabella/blob/master/skills/cluster-3-wearable/23-dyndns/images/DNS.png)

Here is an image of the domain displaying text on a computer and a phone:

![computer](https://github.com/BU-EC444/Kuhl-Isabella/blob/master/skills/cluster-3-wearable/23-dyndns/images/domain.png)

![mobile](https://github.com/BU-EC444/Kuhl-Isabella/blob/master/skills/cluster-3-wearable/23-dyndns/images/mobileTest.png)

Here is an image of port forwarding configuration:

![port forwarding](https://github.com/BU-EC444/Kuhl-Isabella/blob/master/skills/cluster-3-wearable/23-dyndns/images/portForwarding.png)


## Modules, Tools, Source Used in Solution

* We used [namecheap](https://www.namecheap.com/) to register a domain name for our server.

-----

## Reminders
- Repo is private
