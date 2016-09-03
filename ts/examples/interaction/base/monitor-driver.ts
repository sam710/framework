﻿/// <reference path="../../typings/samchon-framework/samchon-framework.d.ts" />

import samchon = require("samchon-framework");

namespace monitor
{
	import library = samchon.library;
	import protocol = samchon.protocol;

	export interface ISystem extends protocol.IProtocol, protocol.IEntity
	{
		// private uid: number;

		// private set_uid(val: number): void;
	}

	export class MonitorDriver implements protocol.IProtocol
	{
		private system: ISystem;
		private connector: protocol.ServerConnector;

		/* ---------------------------------------------------------
			CONSTRUCTORS
		--------------------------------------------------------- */
		public constructor(system: ISystem)
		{
			this.system = system;

			this.connector = new protocol.ServerConnector(this);
			this.connector.connect("127.0.0.1", 37900);
		}

		/* ---------------------------------------------------------
			INVOKE MESSAGE CHAIN
		--------------------------------------------------------- */
		//--------
		// SEND_DATA
		//--------
		public sendData(invoke: protocol.Invoke): void
		{
			this.connector.sendData(invoke);
		}

		public notifySendData(to: number, invoke: protocol.Invoke): void
		{
			if (this.system["uid"] == -1 || to == -1)
				return;

			this.sendData(new protocol.Invoke("notifySendData", this.system["uid"], to, invoke.getListener()));
		}

		public sendSystemStructure(): void
		{
			if (this.system["uid"] == -1)
				return;

			let xml: library.XML = this.system.toXML();

			if (this.system instanceof protocol.external.ExternalSystemArray)
			{
				let system_array: protocol.external.ExternalSystemArray = this.system as protocol.external.ExternalSystemArray;

				for (let i: number = 0; i < system_array.size(); i++)
					if (system_array.at(i)["uid"] == -1)
						return;

				xml.setTag("system");
			}
			this.sendData(new protocol.Invoke("construct", xml));
		}

		//--------
		// REPLY_DATA
		//--------
		public replyData(invoke: protocol.Invoke): void
		{
			invoke.apply(this);
		}

		private set_uid(val: number): void
		{
			this.system["set_uid"](val);
		}
	}
}

export = monitor;