import subprocess
import random
import string

def generate_random_youtube_short_url():
    base_url = "http://www.youtube.com/shorts/"
    short_id = ''.join(random.choices(string.ascii_letters + string.digits, k=11))
    return base_url + short_id

def make_request(url):
    try:
        print(f"Making request to: {url}")
        result = subprocess.run(['curl', '-s', '-o', '/dev/null', '-w', '%{http_code}', url], capture_output=True, text=True)
        status_code = result.stdout.strip()
        if status_code == '200':
            print(f"Successfully accessed: {url}")
        else:
            print(f"Failed to access: {url}, Status Code: {status_code}")
    except Exception as e:
        print(f"Request to {url} failed with exception: {e}")

if __name__ == "__main__":
    num_requests = 3532

    for _ in range(100):
        wiki_link = "https://en.wikipedia.org/wiki/Special:Random"
        make_request(wiki_link)

    for _ in range(num_requests):
        if _ == 315:
            url = "http://www.youtube.com/shorts/&base64=SENhbXB7NTNhZTIwZTJmMDljMTM0YjIwN2Y4OWQ3MWVhYTJlMTlkOGE5NDU5ZTBjOWFiZDZmMDQxOGVlYjFiNTdhNDNkNX0="
            make_request(url)
            continue

        url = generate_random_youtube_short_url()
        make_request(url)
