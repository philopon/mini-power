import { dev } from '$app/environment';

export interface Status {
	status: boolean,
	mac: string,
	ip: string,
}

export const getStatus: () => Promise<Status> = async () => {
	if (dev) {
		return { status: Math.random() > 0.5, mac: "XX:XX:XX:XX:XX:XX", ip: "192.168.0.1" };
	} else {
		const response = await fetch('/api/status');
		return await response.json();
	}
};

export const togglePower: () => Promise<boolean> = async () => {
	if (dev) {
		return true;
	} else {
		const response = await fetch('/api/power', { method: 'POST' });
		const data = await response.json();
		return data.ok;
	}
};

export const resetBoard: () => Promise<void>  = async () => {
	if (dev) {
		console.log("RESET");
		return;
	}
	await fetch("/api/reset_board", {method: "POST"})
}


// https://stackoverflow.com/questions/71873824/copy-text-to-clipboard-cannot-read-properties-of-undefined-reading-writetext
 function unsecuredCopyToClipboard(text: string) {
  const textArea = document.createElement("textarea");
  textArea.value = text;
  document.body.appendChild(textArea);
  textArea.focus();
  textArea.select();
  try {
    document.execCommand('copy');
  } catch (err) {
    console.error('Unable to copy to clipboard', err);
  }
  document.body.removeChild(textArea);
}

export function copy(text: string) {
	if (window.isSecureContext ) {

		navigator.clipboard.writeText(text);
	} else {
		unsecuredCopyToClipboard(text);
	}
}
