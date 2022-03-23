window.onload = () => {
    const submitButton = document.getElementById("submit")
    const roomNameField = document.getElementById('roomNameField')

    console.log(roomNameField)

    submitButton.onclick = () =>{
        const numberField = document.getElementById('numberPeopleField')

        const roomName = roomNameField.value
        const number = numberField.value
        console.log(number)

        location.href = location.href + '/' + roomName + '/' + number
    }
}